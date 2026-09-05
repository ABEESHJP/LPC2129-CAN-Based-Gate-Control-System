#ifndef __DELAY_H_
#define __DELAY_H_

#include <LPC21xx.H>

void delay_milliseconds(unsigned int ms)
{
	T0PR = 60000 - 1;

	T0TCR = 0x01;

	while(T0TC < ms);

	T0TCR |= 0x02;

	T0TCR = 0x00;
}

#endif
