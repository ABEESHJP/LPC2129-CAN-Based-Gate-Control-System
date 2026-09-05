#ifndef __HEADER_H_
#define __HEADER_H_

#define PORT0 0
#define PORT1 1

#define SET   1
#define CLEAR 0

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short int u16;
typedef signed short int s16;

typedef struct CAN2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}CAN2_MSG;

/* CAN message ID */
#define ADC_MSG_ID 0x150

/* ADC level thresholds */
#define LEVEL1_MAX 1365
#define LEVEL2_MAX 2730

/* CAN driver */
void can2_init(void);
void can2_tx(CAN2_MSG m1);
void can2_rx(CAN2_MSG *m1);

/* UART0 */
void uart0_init(u32 baud);
void uart0_tx(u8 ch);
u8 uart0_rx(void);
void uart0_tx_string(s8 *s);
void uart0_tx_integer(s32 n);
void uart0_tx_hex(int num);

/* SPI / MCP3204 */
void Init_SPI0(void);
u8 SPI0(u8 data);
u32 Read_ADC_MCP3204(u8 channelNo);

/* Servo */
void servo_init(void);
void servo_move_to(int target);

#endif

