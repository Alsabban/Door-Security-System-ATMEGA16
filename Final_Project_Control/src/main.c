/******************************************************************************
 *
 * Module: Controller for Door Lock System
 *
 * File Name: main.c
 *
 * Description: Source file for the Door Lock Controller
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/


/*******************************************************************************
 *                      		Includes	                                   *
 *******************************************************************************/
#include "timers.h"
#include "uart.h"
#include "i2c.h"
#include "external_eeprom.h"
#include "dc_motor.h"
#include <avr/io.h>
#include <util/delay.h>


/*******************************************************************************
 *                      	Define Macros	                                   *
 *******************************************************************************/
//#define TESTING
#define PASSWORD_ADDRESS 0x311
#define MC_READY 0x10
#define DIFFERENT_PASSWORDS 0x01
#define CHANGE_SUCCESS 0x02
#define WRONG_PASSWORD 0x03
#define RIGHT_PASSWORD 0x04
#define PASSWORD_SIZE 6

/*******************************************************************************
 *                      Configuration Structs                                  *
 *******************************************************************************/

UART_configType UART_config = {
		DOUBLE,
		NORMAL,
		RECEIVE_INT_DISABLE,
		SEND_INT_DISABLE,
		EMPTY_INT_DISABLE,
		RECEIVE_ENABLE,
		SEND_ENABLE,
		OTHER,
		ASYNCHRONOUS,
		STOP_1_BIT,
		NO_PARITY,
		EIGHT_OR_NINE_BIT_MODE,
		RISING_TxD,
		9600
};
TIMER0_configType TIMER0_config = {
		NORMAL_MODE,
		FCPU_1024,
		TOGGLE_OC0_ON_MATCH,
		COMPARE_MATCH_INTERRUPT_ENABLE,
		5,
		0
};
I2C_configType I2C_config = {
		0x02,
		PRESCALER_1,
		0x01,
		I2C_ENABLE,
		I2C_INT_DISABLE
};

/*******************************************************************************
 *                      Global Variables	                                   *
 *******************************************************************************/
/* Number of ticks performed by Timer0 */
short int timerTicks = 0;
/* Password sent through HMI */
unsigned char password[PASSWORD_SIZE + 1];
/* Second password writing in case of changing passwords */
unsigned char confirmPassword[PASSWORD_SIZE + 1];

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void timerHandler(void);
void openDoor(void);
uint8 recvCheckPassword(void);
uint8 recvChangePassword(void);
void getCommand(void);

/*******************************************************************************
 *                      	Main Function	                                   *
 *******************************************************************************/
int main(void) {
	/* Set the I bit */
	SREG |= (1 << 7);
	/* initialize UART */
	UART_init(&UART_config);
	/* set timer callback function to the "timerHandler" function */
	TIMER0_setCallback(timerHandler);
	/* Initialize I2C */
	I2C_init(&I2C_config);
	/* Motor Initialization */
	DcMotor_Init();
	/* Set the first password. Loop doesn't break unless HMI writes identical passwords */
	while (!(recvChangePassword()))
		;

	while (1) {
		/* Checks if password is correct doesn't reach "getCommand" unless password is correct */
		if (!(recvCheckPassword())) {
			continue;
		}
		/* Open or change the password depending on the HMI choice */
		getCommand();

	}
}


/*******************************************************************************
 *                      Function Definitions                                   *
 *******************************************************************************/
/* Description:
 * Timer ISR.
 * Increments the tick counter (global variable) by one.
 */
void timerHandler(void) {
	timerTicks++;
}


/* Description:
 * Initializes the timer0 module according to the configuration structure given.
 * Spins the motor clockwise for 15 seconds then stops for 3 seconds and finally spins
 * anti-clockwise for 15 seconds before stopping the motor and the timer0 module.
 */
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

/* Description:
 * Receives the password from the HMI then compares the received password with the
 * password stored in the EEPROM module. Sends a confirmation byte through UART if
 * the passwords match or a different byte in case the passwords don't match.
 *
 * Returns:
 * 1: in case the confirmation byte is sent
 * 0: a different byte is sent
 */
uint8 recvCheckPassword(void) {
	/* This MC is ready to receive */
	UART_sendByte(MC_READY);
	UART_receiveString(password);
	int i = 0;

	/* Flag confirming success in case its value stays at 1 */
	char passFlag = 1;

	/* Wait until the other MC is ready */
	while (UART_recieveByte() != MC_READY) {
	}

	/* Password string to be compared with, set to 111111 in case of testing
	 * without using the EEPROM module
	 */
	uint8 pass[PASSWORD_SIZE + 1] = { '1', '1', '1', '1', '1', '1', '\0' };
#ifndef TESTING
	/* Read from the EEPROM module and store in the "pass" array */
	while(i<PASSWORD_SIZE){
		EEPROM_readByte((PASSWORD_ADDRESS+i), (pass+i));
		_delay_ms(10);
		i++;
	}
#endif
	i = 0;
	/* Compare between received password and the stored Password */
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

/* Description:
 * Receives a password written twice on the HMI and checks both writings. If two
 * writings match then the password is written on the EEPROM module and a confirmation
 * byte is sent through UART. Otherwise, a different byte is sent indicating different
 * writings.
 *
 * Returns:
 * 1: in case the confirmation byte is sent
 * 0: a different byte is sent
 */
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
		/* Write the new password into the EEPROM module */
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

/* Description:
 * Receives a character from the HMI. If this character is '+' then the controller opens
 * the door. If the character is '-' then the controller goes to change the password.
 */
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
