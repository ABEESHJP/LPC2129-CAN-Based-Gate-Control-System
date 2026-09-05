/* node1_main.c -- Node1: reads the water-level sensor via the MCP3204
   (SPI0), broadcasts the raw 12-bit value over CAN2 to Node2 (LCD+LED)
   and Node3 (servo). */
#include "header.h"
#include "delay.h"

main(){
	CAN2_MSG m1;
	u32 adc_val;

	can2_init();
	Init_SPI0();

	m1.id  = ADC_MSG_ID;
	m1.rtr = 0;                  //data frame
	m1.dlc = 2;

	while(1){
		adc_val = Read_ADC_MCP3204(0);   //channel 0

		m1.byteA = adc_val;               //raw 12-bit code (0-4095)
		m1.byteB = 0;

		can2_tx(m1);

		delay_milliseconds(200);          //sample/broadcast rate -- tune as needed
	}
}
