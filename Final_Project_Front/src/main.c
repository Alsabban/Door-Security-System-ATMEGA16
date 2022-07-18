/******************************************************************************
 *
 * Module: HMI for Door Lock System
 *
 * File Name: main.c
 *
 * Description: Source file for the HMI for the Door Lock Control System
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/


/*******************************************************************************
 *                      		Includes	                                   *
 *******************************************************************************/
#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include <avr/io.h>
#include <util/delay.h>
#include "buzzer.h"

/*******************************************************************************
 *                      	Define Macros	                                   *
 *******************************************************************************/
#define MC_READY 0x10
#define DIFFERENT_PASSWORDS 0x01
#define CHANGE_SUCCESS 0x02
#define WRONG_PASSWORD 0x03
#define RIGHT_PASSWORD 0x04
#define PASSWORD_SIZE 6

/*******************************************************************************
 *                      Configuration Structs                                  *
 *******************************************************************************/

UART_configType UART_config = { DOUBLE, NORMAL, RECEIVE_INT_DISABLE,
		SEND_INT_DISABLE, EMPTY_INT_DISABLE, RECEIVE_ENABLE, SEND_ENABLE, OTHER,
		ASYNCHRONOUS, STOP_1_BIT, NO_PARITY, EIGHT_OR_NINE_BIT_MODE, RISING_TxD,
		9600 };

/*******************************************************************************
 *                      Global Variables	                                   *
 *******************************************************************************/
unsigned char password[PASSWORD_SIZE + 1];
unsigned char confirmPassword[PASSWORD_SIZE + 1];
uint8 false_counter = 0;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void newPassword(char *str, char *confirm);
uint8 changePassword(void);
void enterPassword(char *str);
uint8 sendPassword(void);
void loggedIn(void);
void intruderAlert(void);

/*******************************************************************************
 *                      	Main Function	                                   *
 *******************************************************************************/

int main(void) {
	UART_init(&UART_config);
	LCD_init();
	BUZZER_init();
	/* First password */
	while (1) {
		newPassword(password, confirmPassword);
		if (changePassword())
			break;
	}

	while (1) {
		/* Password was entered wrong three consecutive times */
		if (false_counter >= 3) {
			intruderAlert();
		}
		/* Ask for password */
		enterPassword(password);
		if (sendPassword()) {
			loggedIn();
			false_counter = 0;
		}
	}

}

/*******************************************************************************
 *                      Function Definitions                                   *
 *******************************************************************************/

/* Description:
 * Asks user to type a password twice on the keypad and save each time in a different
 * string to be sent to and compared by the control unit
 */
void newPassword(char *str, char *confirm) {
	LCD_CLEAR_SCREEN();
	LCD_moveCursor(0, 0);
	LCD_displayString("Enter a Password");
	LCD_moveCursor(1, 0);
	char i = 0;
	while (i < PASSWORD_SIZE) {
		str[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		i++;
		_delay_ms(30);
	}
	str[PASSWORD_SIZE] = '#';

	LCD_CLEAR_SCREEN();

	LCD_moveCursor(0, 0);
	LCD_displayString("Re-Enter");
	LCD_moveCursor(1, 0);
	i = 0;
	while (i < PASSWORD_SIZE) {
		confirm[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		i++;
		_delay_ms(30);
	}
	confirm[PASSWORD_SIZE] = '#';
}

/* Description:
 * User enters the password on the keypad, password is saved to a string to be sent
 * later to the control unit.
 */
void enterPassword(char *str) {
	LCD_CLEAR_SCREEN();
	LCD_moveCursor(0, 0);
	LCD_displayString("Enter Password");
	LCD_moveCursor(1, 0);
	char i = 0;
	while (i < PASSWORD_SIZE) {
		str[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		i++;
		_delay_ms(30);
	}
	str[PASSWORD_SIZE] = '#';
}

/* Description:
 * HMI sends both passwords to the control unit to be compared. The function then receives
 * a byte indicating whether the password change was successful or not.
 *
 * Returns:
 * 1: Successful password change
 * 0: Unsuccessful password change
 */
uint8 changePassword(void) {
	while (UART_recieveByte() != MC_READY) {
	}
	UART_sendString(password);
	while (UART_recieveByte() != MC_READY) {
	}
	UART_sendString(confirmPassword);
	UART_sendByte(MC_READY);
	uint8 val = UART_recieveByte();
	if (val == DIFFERENT_PASSWORDS) {
		return 0;
	} else if (val == CHANGE_SUCCESS) {
		return 1;
	}

}

/* Description:
 * HMI sends the password to the control unit to be checked. Receives a byte indicating
 * whether the password was correct or incorrect.
 *
 * Returns:
 * 1: Password was correct
 * 0: Password Incorrect
 */
uint8 sendPassword(void) {
	while (UART_recieveByte() != MC_READY) {
	}
	UART_sendString(password);
	UART_sendByte(MC_READY);
	char val = UART_recieveByte();
	if (val == RIGHT_PASSWORD) {
		return 1;
	} else {
		false_counter++;
		return 0;
	}
}

/* Description:
 * Asks the user to chose between opening the door ('+') or changing the password ('-').
 * Function disregards any keypad press other than the '+' or '-' buttons. Either characters
 * are sent to the control unit and the control unit reacts as requested.
 */
void loggedIn(void) {

	while (UART_recieveByte() != MC_READY) {
	}
	uint8 var;
	LCD_CLEAR_SCREEN();
	LCD_moveCursor(0, 0);
	LCD_displayString("+: Open Door");
	LCD_moveCursor(1, 0);
	LCD_displayString("-: Change Password");
	while (1) {
		var = KEYPAD_getPressedKey();
		if (var == '+' || var == '-') {
			UART_sendByte(var);
			if (var == '+') {
				LCD_CLEAR_SCREEN();
				LCD_moveCursor(0, 0);
				LCD_displayString("Opening...");

				/* Wait till door finishes opening */
				while (UART_recieveByte() != MC_READY) {
				}
			} else if (var == '-') {
				while (1) {
					newPassword(password, confirmPassword);
					if (changePassword())
						break;
				}
			}
			break;
		}
	}

}


/*Description:
 * Turns on the buzzer and stops on an LCD message "INTRUDER!!!" for a minute then resets
 * the false password count.
 */
void intruderAlert(void){
	BUZZER_on();
	LCD_CLEAR_SCREEN();
	LCD_moveCursor(0, 0);
	LCD_displayString("INTRUDER!!!");
	_delay_ms(60000);
	BUZZER_off();
	false_counter = 0;
}

