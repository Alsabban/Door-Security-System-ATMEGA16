#include "timers.h"
#include "uart.h"
#include "i2c.h"
#include <avr/io.h>
#define MC2_READY 0x10
void main(void) {
	DDRB=255;
	UART_configType UART_config = { DOUBLE, NORMAL, RECEIVE_INT_DISABLE,
			SEND_INT_DISABLE, EMPTY_INT_DISABLE, RECEIVE_ENABLE, SEND_ENABLE,
			OTHER, ASYNCHRONOUS, STOP_1_BIT, NO_PARITY, EIGHT_OR_NINE_BIT_MODE,
			RISING_TxD, 9600 };
	TIMER0_configType TIMER0_config = { CTC, FCPU_1024,
			TOGGLE_OC0_ON_MATCH_NON_PWM, DISABLE_INTERRUPTS, 0, 255 };
	I2C_configType I2C_config = { 0x02, PRESCALER_1, 0x01, I2C_ENABLE,
			I2C_INT_DISABLE };
	UART_init(&UART_config);
	TIMER0_init(&TIMER0_config);
	I2C_init(&I2C_config);

	/* Wait until MC2 is ready to receive the string */
	while (UART_recieveByte() != MC2_READY) {
	}

	/* Send the required string to MC2 through UART */
	UART_sendString("hello#");
	while(1){

	}
}
