/*header.h  -- shared across Node1 (SPI ADC/TX), Node2 (LCD+LED/RX), Node3 (Servo/RX) */
#ifndef __HEADER_H_
#define __HEADER_H_

#define PORT0 0
#define PORT1 1
#define SET   1
#define CLEAR 0
typedef  unsigned int u32;
typedef  signed int s32;
typedef  unsigned char u8;
typedef  signed char s8;
typedef  unsigned short int u16;
typedef   signed short int s16;

typedef struct CAN2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}CAN2_MSG;

/* ---- CAN message ID used for the ADC broadcast (Node1 -> Node2, Node3) ---- */
#define ADC_MSG_ID   0x150

/* ---- Level thresholds on the raw 12-bit MCP3204 code (0-4095) ---- */
#define LEVEL1_MAX   1365   /* 0    .. 1365 -> Level 1 */
#define LEVEL2_MAX   2730   /* 1366 .. 2730 -> Level 2 */
                              /* 2731 .. 4095 -> Level 3 */

/* ---- CAN driver (from can2_driver.c) ---- */
void can2_init(void);
void can2_tx(CAN2_MSG m1);
void can2_rx(CAN2_MSG *m1);

/* ---- UART0 driver (debug/logging, optional) ---- */
void uart0_init(u32 baud);
void uart0_tx(u8 ch);
u8 uart0_rx(void);
void uart0_tx_string(s8 *s);
void uart0_tx_integer(s32 n);
void uart0_tx_hex(int num);

/* ---- SPI / MCP3204 ADC driver (Node1) -- see spi_adc.c ---- */
void Init_SPI0(void);
u8   SPI0(u8 data);
u32  Read_ADC_MCP3204(u8 channelNo); /* returns raw 12-bit code, 0-4095 */

/* ---- Servo driver via PWM1 (Node3) ---- */
void servo_init(void);
void servo_set_angle(u16 angle_deg); /* 0 - 180 */

#endif
