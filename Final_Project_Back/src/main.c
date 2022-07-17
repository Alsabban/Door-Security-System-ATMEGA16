#include "timers.h"
#include "uart.h"
#include "i2c.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include <avr/io.h>
#include <util/delay.h>


#define TESTING
#define PASSWORD_ADDRESS 0x311
#define MC_READY 0x10
#define DIFFERENT_PASSWORDS 0x01
#define CHANGE_SUCCESS 0x02
#define WRONG_PASSWORD 0x03
#define RIGHT_PASSWORD 0x04
#define PASSWORD_SIZE 6


UART_configType UART_config = { DOUBLE, NORMAL, RECEIVE_INT_DISABLE,
		SEND_INT_DISABLE, EMPTY_INT_DISABLE, RECEIVE_ENABLE, SEND_ENABLE, OTHER,
		ASYNCHRONOUS, STOP_1_BIT, NO_PARITY, EIGHT_OR_NINE_BIT_MODE, RISING_TxD,
		9600 };
TIMER0_configType TIMER0_config = { NORMAL_MODE, FCPU_1024, TOGGLE_OC0_ON_MATCH,
		COMPARE_MATCH_INTERRUPT_ENABLE, 5, 0 };
I2C_configType I2C_config = { 0x02, PRESCALER_1, 0x01, I2C_ENABLE,
		I2C_INT_DISABLE };


short int timerTicks = 0;
unsigned char password[PASSWORD_SIZE + 1];
unsigned char confirmPassword[PASSWORD_SIZE + 1];


void timerHandler(void);
void openDoor(void);
uint8 recvCheckPassword(void);
uint8 recvChangePassword(void);
void getCommand(void);


int main(void) {
	SREG |= (1 << 7);
	UART_init(&UART_config);
	TIMER0_setCallback(timerHandler);
	I2C_init(&I2C_config);
	DcMotor_Init();
	/* Wait until MC2 is ready to receive the string */
	while (!(recvChangePassword()))
		;

	while (1) {
		if (!(recvCheckPassword())) {
			continue;
		}
		getCommand();

	}
}






void timerHandler(void) {
	timerTicks++;
}

void openDoor(void) {
	timerTicks = 0;
	TIMER0_init(&TIMER0_config);
	DcMotor_Rotate(CLOCKWISE);
	while (timerTicks < 60)
		;
	timerTicks = 0;
	DcMotor_Rotate(STOP);
	while (timerTicks < 20)
		;
	DcMotor_Rotate(ANTICLOCKWISE);
	timerTicks = 0;
	while (timerTicks < 60)
		;
	DcMotor_Rotate(STOP);
	TIMER0_deinit();
	timerTicks = 0;

}

uint8 recvCheckPassword(void) {
	UART_sendByte(MC_READY);
	UART_receiveString(password);
	int i = 0;
	char passFlag = 1;
	while (UART_recieveByte() != MC_READY) {
	}
	uint8 pass[PASSWORD_SIZE + 1] = { '1', '1', '1', '1', '1', '1', '\0' };
#ifndef TESTING
	while(i<PASSWORD_SIZE){
		EEPROM_readByte((PASSWORD_ADDRESS+i), (pass+i));
		_delay_ms(10);
		i++;
	}
#endif
	i = 0;
	while (password[i] != '\0') {
		if (password[i] != pass[i]) {
			passFlag = 0;
			UART_sendByte(WRONG_PASSWORD);
		}
		i++;
	}
	if (passFlag == 1)
		UART_sendByte(RIGHT_PASSWORD);
	return passFlag;
}

uint8 recvChangePassword(void) {
	UART_sendByte(MC_READY);
	UART_receiveString(password);
	UART_sendByte(MC_READY);
	UART_receiveString(confirmPassword);
	int i = 0;
	uint8 passFlag = 1;
	while (UART_recieveByte() != MC_READY) {
	}
	while (password[i] != '\0') {
		if (password[i] != confirmPassword[i]) {
			UART_sendByte(DIFFERENT_PASSWORDS);
			_delay_ms(10);
			passFlag = 0;
		}
		i++;
	}

	if (passFlag == 1) {
		i = 0;
#ifndef TESTING
		while(i<PASSWORD_SIZE){
			EEPROM_writeByte(PASSWORD_ADDRESS+i, password[i]);
			_delay_ms(10);
			i++;
		}
#endif
		UART_sendByte(CHANGE_SUCCESS);
		_delay_ms(10);
	}
	return passFlag;
}

void getCommand(void) {
	UART_sendByte(MC_READY);
	uint8 receivedCommand = UART_recieveByte();
	if (receivedCommand == '+') {
		openDoor();
		UART_sendByte(MC_READY);
	} else if (receivedCommand == '-') {
		while (!(recvChangePassword()))
			;
	}
}
