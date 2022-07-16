 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#include <util/delay.h>
#include "common_macros.h"
#include "lcd.h"
#include "gpio.h"

void LCD_init(void) {
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RW_PORT_ID, LCD_RW_PIN_ID, PIN_OUTPUT);
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PIN_OUTPUT);
	LCD_TWO_LINES_8BITS_MODE();
	LCD_CURSOR_OFF();
	LCD_CLEAR_SCREEN();
}

void LCD_sendCommand(uint8 command) {
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}

void LCD_displayCharacter(uint8 data) {
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT_ID, data);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);
}

void LCD_displayString(const uint8 * data){
	int i=0;
	while(data[i]!='\0'){
		LCD_displayCharacter(*(data+i));
		i++;
	}
}

void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_SET_CURSOR_LOCATION(lcd_memory_address);
}

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_integerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_displayString(buff); /* Display the string */
}
