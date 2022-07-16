#include "timers.h"
#include "uart.h"
#include "i2c.h"
#include "dc_motor.h"
#include <avr/io.h>
#define MC2_READY 0x10

char timerTicks=0;

void timerHandler(void);

void main(void) {
	DDRB=255;
	UART_configType UART_config = { DOUBLE, NORMAL, RECEIVE_INT_DISABLE,
			SEND_INT_DISABLE, EMPTY_INT_DISABLE, RECEIVE_ENABLE, SEND_ENABLE,
			OTHER, ASYNCHRONOUS, STOP_1_BIT, NO_PARITY, EIGHT_OR_NINE_BIT_MODE,
			RISING_TxD, 9600 };
	TIMER0_configType TIMER0_config = { CTC, FCPU_1024,
			OC0_DISCONNECTED, COMPARE_MATCH_INTERRUPT_ENABLE, 0, 250 };
	I2C_configType I2C_config = { 0x02, PRESCALER_1, 0x01, I2C_ENABLE,
			I2C_INT_DISABLE };
	UART_init(&UART_config);
	TIMER0_init(&TIMER0_config);
	TIMER0_setCallback(timerHandler);
	I2C_init(&I2C_config);
	DcMotor_Init();
	DcMotor_Rotate(CLOCKWISE);

	/* Wait until MC2 is ready to receive the string */
	while (UART_recieveByte() != MC2_READY) {
	}

	/* Send the required string to MC2 through UART */
	UART_sendString("hello#");
	while(1){

	}
}

void timerHandler(void){
	timerTicks++;
}

void openDoor(void){

}
