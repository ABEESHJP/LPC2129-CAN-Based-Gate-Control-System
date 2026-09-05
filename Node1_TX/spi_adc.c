/*spi_adc.c -- Node1: reads the external MCP3204 ADC over SPI0.
  Adapted from your adc.c: identical SPI/CS/timing logic, the only change
  is Read_ADC_MCP3204() now returns the raw 12-bit code (0-4095) instead
  of converting to a float voltage, since that's what goes out over CAN.
  If you want the voltage for a display, convert on the receiving side:
      voltage = (raw * 3.3f) / 4095.0f */
#include <LPC21xx.H>
#include "header.h"

#define Mode_0 0x00

void Init_SPI0(void)
{
	/* Configure P0.4, P0.5 and P0.6 for SPI */
	PINSEL0 &= ~(0x00003F00);
	PINSEL0 |= 0x00001500;

	/* SPI clock */
	S0SPCCR = 10;

	/* SPI Master, Mode 0 */
	S0SPCR = (1 << 5) | Mode_0;

	/* P0.7 as output for Chip Select */
	IODIR0 |= (1 << 7);

	/* CS HIGH */
	IOSET0 = (1 << 7);
}

u8 SPI0(u8 data)
{
	S0SPDR = data;

	/* Wait until SPI transfer is complete */
	while((S0SPSR & (1 << 7)) == 0);

	return S0SPDR;
}

u32 Read_ADC_MCP3204(u8 channelNo)
{
	u8 hbyte, lbyte;
	u32 adcVal;

	/* CS LOW */
	IOCLR0 = (1 << 7);

	/* Start bit + single-ended mode */
	SPI0(0x06);

	/* Channel selection */
	hbyte = SPI0(channelNo << 6);

	/* Read remaining 8 bits */
	lbyte = SPI0(0x00);

	/* CS HIGH */
	IOSET0 = (1 << 7);

	/* Extract 12-bit ADC value */
	adcVal = ((hbyte & 0x0F) << 8) | lbyte;

	return adcVal; /* raw code, 0-4095 */
}
