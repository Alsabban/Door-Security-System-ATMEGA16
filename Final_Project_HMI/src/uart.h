/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART module driver for AVR microcontrollers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum {
	DOUBLE = 0x02, NO_DOUBLE = 0x00
} UART_UCSRA_U2X;

typedef enum {
	MULTIPROCESSOR = 0x01, NORMAL = 0x00
} UART_UCSRA_MPCM;

typedef enum {
	RECEIVE_INT_ENABLE = 0x80, RECEIVE_INT_DISABLE = 0x00
} UART_UCSRB_RXCIE;

typedef enum {
	SEND_INT_ENABLE = 0x40, SEND_INT_DISABLE = 0x00
} UART_UCSRB_TXCIE;

typedef enum {
	EMPTY_INT_ENABLE = 0x20, EMPTY_INT_DISABLE = 0x00
} UART_UCSRB_UDRIE;

typedef enum {
	RECEIVE_ENABLE = 0x10, RECEIVE_DISABLE = 0x00
} UART_UCSRB_RXEN;

typedef enum {
	SEND_ENABLE = 0x08, SEND_DISABLE = 0x00
} UART_UCSRB_TXEN;

typedef enum {
	NINE_BIT_MODE = 0x04, OTHER = 0x00
} UART_UCSRB_UCSZ2;

typedef enum {
	SYNCHRONOUS = 0x40, ASYNCHRONOUS = 0x00
} UART_UCSRC_UMSEL;

typedef enum {
	NO_PARITY = 0x00, EVEN_PARITY = 0x20, ODD_PARITY = 0x30
} UART_UCSRC_UPM;

typedef enum {
	STOP_2_BITS = 0x08, STOP_1_BIT = 0x00
} UART_UCSRC_USBS;

typedef enum {
	EIGHT_OR_NINE_BIT_MODE = 0x06,
	SEVEN_BIT_MODE = 0x04,
	SIX_BIT_MODE = 0x02,
	FIVE_BIT_MODE = 0x00
} UART_UCSRC_UCSZ;

typedef enum {
	RISING_TxD = 0x00, FALLING_TxD = 0x01
} UART_UCSRC_UCPOL;


typedef struct {
	UART_UCSRA_U2X doubleRate;
	UART_UCSRA_MPCM multiprocessorMode;
	UART_UCSRB_RXCIE receiveIntEnable;
	UART_UCSRB_TXCIE sendIntEnable;
	UART_UCSRB_UDRIE emptyIntEnable;
	UART_UCSRB_RXEN receiveEnable;
	UART_UCSRB_TXEN sendEnable;
	UART_UCSRB_UCSZ2 nineBitMode;
	UART_UCSRC_UMSEL modeSelect;
	UART_UCSRC_USBS stopBits;
	UART_UCSRC_UPM parityMode;
	UART_UCSRC_UCSZ bitNumSelect;
	UART_UCSRC_UCPOL clockPolarity;
	uint16 baudRate;
} UART_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_configType* config);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
