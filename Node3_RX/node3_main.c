/* node3_main.c -- Node3: receives ADC from Node1 and drives the gate servo

   Level 1 -> Gate CLOSED
              Servo = 0 degree

   Level 2 -> Gate opens 0 -> 90 degree
              proportional to ADC value

   Level 3 -> Gate opens 90 -> 180 degree
              proportional to ADC value
*/

#include "header.h"

main()
{
	CAN2_MSG rx;
	u32 value;
	u32 pwm_value;

	can2_init();

	servo_init();

	while(1)
	{
		can2_rx(&rx);

		if(rx.id == ADC_MSG_ID && rx.rtr == 0)
		{
			value = rx.byteA;

			/* Level 1 */

			if(value <= LEVEL1_MAX)
			{
				servo_move_to(7500);
			}

			/* Level 2 */

			else if(value <= LEVEL2_MAX)
			{
				pwm_value = 7500 +
					((value - LEVEL1_MAX) * 14250)
					/ (LEVEL2_MAX - LEVEL1_MAX);

				servo_move_to(pwm_value);
			}

			/* Level 3 */

			else
			{
				pwm_value = 21750 +
					((value - LEVEL2_MAX) * 14250)
					/ (4095 - LEVEL2_MAX);

				servo_move_to(pwm_value);
			}
		}
	}
}

