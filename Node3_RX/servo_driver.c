/* servo_driver.c -- Node3: Servo control using PWM3 on P0.1 */

#include <LPC21xx.H>
#include "header.h"
#include "delay.h"

void servo_init(void)
{
	VPBDIV = 1;			// PCLK = CCLK = 60MHz

	PINSEL0 = 0x08;			// P0.1 = PWM3

	PWMPR = 3;			// 60MHz/(3+1) = 15MHz

	PWMMR0 = 300000 - 1;		// 20ms period = 50Hz

	PWMMR3 = 7500;			// Initial position

	PWMMCR = 0x00000003;		// Reset TC on MR0 match

	PWMPCR = 0x00000800;		// Enable PWM3

	PWMTCR = 0x00000009;		// Enable PWM and counter

	PWMLER = 0x08;			// Latch MR3
}


void servo_move_to(int target)
{
	static int position = 7500;
	int i;

	/* Move servo in positive direction */

	if(position < target)
	{
		for(i = position; i <= target; i += 100)
		{
			PWMMR3 = i;

			PWMLER = 0x08;

			delay_milliseconds(10);
		}
	}

	/* Move servo in negative direction */

	else if(position > target)
	{
		for(i = position; i >= target; i -= 100)
		{
			PWMMR3 = i;

			PWMLER = 0x08;

			delay_milliseconds(10);
		}
	}

	/* Save new servo position */

	position = target;
}
