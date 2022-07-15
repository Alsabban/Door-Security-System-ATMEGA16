#include "uart.h"
#include "lcd.h"
#include <avr/io.h>
#define MC2_READY 0x10
int main(void) {
	UART_configType UART_config = { DOUBLE, NORMAL, RECEIVE_INT_DISABLE,
			SEND_INT_DISABLE, EMPTY_INT_DISABLE, RECEIVE_ENABLE, SEND_ENABLE,
			OTHER, ASYNCHRONOUS, STOP_1_BIT, NO_PARITY, EIGHT_OR_NINE_BIT_MODE,
			RISING_TxD, 9600 };
	UART_init(&UART_config);
	LCD_init();
	uint8 Str[20];
	/* Send MC2_READY byte to MC1 to ask it to send the string */
		UART_sendByte(MC2_READY);

		/* Receive String from MC1 through UART */
		UART_receiveString(Str);

		/* Display the received string on the LCD display */
		LCD_displayString(Str);

	    while(1)
	    {

	    }
}
