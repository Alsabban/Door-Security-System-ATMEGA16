#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include <avr/io.h>
#include <util/delay.h>
#include "buzzer.h"

#define MC_READY 0x10
#define DIFFERENT_PASSWORDS 0x01
#define CHANGE_SUCCESS 0x02
#define WRONG_PASSWORD 0x03
#define RIGHT_PASSWORD 0x04
#define PASSWORD_SIZE 6

unsigned char password[PASSWORD_SIZE + 1];
unsigned char confirmPassword[PASSWORD_SIZE + 1];

void newPassword(char *str, char *confirm);
uint8 changePassword(void);
void enterPassword(char *str);
uint8 sendPassword(void);
void loggedIn(void);

UART_configType UART_config = { DOUBLE, NORMAL, RECEIVE_INT_DISABLE,
		SEND_INT_DISABLE, EMPTY_INT_DISABLE, RECEIVE_ENABLE, SEND_ENABLE, OTHER,
		ASYNCHRONOUS, STOP_1_BIT, NO_PARITY, EIGHT_OR_NINE_BIT_MODE, RISING_TxD,
		9600 };

uint8 false_counter = 0;

int main(void) {
	UART_init(&UART_config);
	LCD_init();
	BUZZER_init();
	while (1) {
		newPassword(password, confirmPassword);
		if (changePassword())
			break;
	}

	while (1) {
		if (false_counter >= 3) {
			BUZZER_on();
			LCD_CLEAR_SCREEN();
			LCD_moveCursor(0, 0);
			LCD_displayString("INTRUDER!!!");
			_delay_ms(60000);
			BUZZER_off();
			false_counter = 0;
		}
		enterPassword(password);
		if (sendPassword()) {
			loggedIn();
			false_counter = 0;
		}
	}

}
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
				LCD_displayString("Openning...");
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

