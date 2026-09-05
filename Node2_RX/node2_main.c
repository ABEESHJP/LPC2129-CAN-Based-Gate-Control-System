/* node2_main.c -- Node2: receives the ADC broadcast from Node1, works out
   which level it falls in, shows "Level X" + the raw code on the LCD
   (your lcd_header.h driver: P0.10-P0.17=data, P0.18=RS, P0.19=E) and
   lights the matching LED.
   LED wiring assumed: LED1->P1.16, LED2->P1.17, LED3->P1.18
   (CHANGE if wired elsewhere) */
#include "header.h"
#include "lcd_header.h"
//#include "delay.h"

#define LED1 (1<<16)
#define LED2 (1<<17)
#define LED3 (1<<18)

static void leds_init(void){
	IODIR1 |= (LED1|LED2|LED3);
	IOSET1  = (LED1|LED2|LED3);
}

/* Power-on sequence step 1: show the project title for a couple of
   seconds before switching over to live level readings. */
static void show_title(void){
	LCD_COMMAND(0x01);                //clear display
	LCD_COMMAND(0x80);                //line 1
	LCD_STR("CAN BUS WATER");
	LCD_COMMAND(0xC0);                //line 2
	LCD_STR("LEVEL GATE CTRL");
	delay_milliseconds(2000);
	LCD_COMMAND(0x01);                //clear before first live reading
}

/*static void show_level(u8 level, u32 adc_val){
	IOCLR1 = (LED1|LED2|LED3);        //all off first

	LCD_COMMAND(0x01);                //clear display
	LCD_COMMAND(0x80);                //line 1

	if(level==1){
		LCD_STR("Level 1  CLOSED");
		IOSET1 = LED1;
	}
	else if(level==2){
		LCD_STR("Level 2  OPENING");
		IOSET1 = LED2;
	}
	else{
		LCD_STR("Level 3  OPEN");
		IOSET1 = LED3;
	}

	LCD_COMMAND(0xC0);                //line 2
	LCD_STR("ADC:");
	LCD_INTEGER((int)adc_val);
} */

static void show_level(u8 level, u32 adc_val)
{
    IOSET1 = (LED1|LED2|LED3);       // First turn OFF all LEDs

    LCD_COMMAND(0x01);
    LCD_COMMAND(0x80);

    if(level==1){
        LCD_STR("Level 1  CLOSED");
        IOCLR1 = LED1;               // LED1 ON
    }
    else if(level==2){
        LCD_STR("Level 2  OPENING");
        IOCLR1 = LED2;               // LED2 ON
    }
    else{
        LCD_STR("Level 3  OPEN");
        IOCLR1 = LED3;               // LED3 ON
    }

    LCD_COMMAND(0xC0);
    LCD_STR("ADC:");
    LCD_INTEGER((int)adc_val);
}

main(){
	CAN2_MSG rx;
	u32 adc_val;
	u8 level;

	can2_init();
	LCD_INIT();
	leds_init();
	show_title();                     //power-on step 1: title splash
	show_level(1, 0);                 //power-on step 2: default to CLOSED
	                                   //until the first CAN reading arrives

	while(1){
		can2_rx(&rx);

		if(rx.id==ADC_MSG_ID && rx.rtr==0){
			adc_val = rx.byteA;

			if(adc_val<=LEVEL1_MAX)      level=1;
			else if(adc_val<=LEVEL2_MAX) level=2;
			else                          level=3;

			show_level(level, adc_val);
		}
	}
}
