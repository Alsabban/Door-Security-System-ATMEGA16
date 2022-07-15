 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/


#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LCD_RS_PORT_ID                 PORTD_ID
#define LCD_RS_PIN_ID                  PIN4_ID

#define LCD_RW_PORT_ID                 PORTD_ID
#define LCD_RW_PIN_ID                  PIN5_ID

#define LCD_E_PORT_ID                  PORTD_ID
#define LCD_E_PIN_ID                   PIN6_ID

#define LCD_DATA_PORT_ID               PORTC_ID


#define LCD_CLEAR_SCREEN() LCD_sendCommand(0x01)
#define LCD_CURSOR_OFF() LCD_sendCommand(0x0c)
#define LCD_CURSOR_ON() LCD_sendCommand(0x0e)
#define LCD_TWO_LINES_8BITS_MODE() LCD_sendCommand(0x38)
#define LCD_GO_TO_HOME() LCD_sendCommand(0x02)
#define LCD_TWO_LINES_4BITS_MODE() LCD_sendCommand(0x28)
#define LCD_SET_CURSOR_LOCATION(lcd_memory_address) LCD_sendCommand(lcd_memory_address|0x80)

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description:
 * -Setup LCD pins direction using GPIO driver
 * -Setup Data mode for 4 bits or 8 bits
 *
 * Inputs: None
 *
 * Returns: None
 */
void LCD_init(void);

/*
 * Description:
 * sends a command from to the LCD from the defined command numbers in the LCD datasheet
 *
 * Inputs: Command Number
 *
 * Returns: None
 */

void LCD_sendCommand(uint8 command);

/*
 * Description:
 * displays a character on the LCD screen
 *
 * Inputs: Character to be displayed
 *
 * Returns: None
 *
 */

void LCD_displayCharacter(uint8 data);

/*
 * Description:
 * -Setup LCD pins direction using GPIO driver
 * -Setup Data mode for 4 bits or 8 bits
 *
 * Inputs: String to be displayed
 *
 * Returns: None
 */

void LCD_displayString(const char* data);

/*
 *
 * Description:
 * Move cursor to specified row and column index
 *
 * Inputs: Row Number (from 0 to 3), column number
 *
 * Returns: None
 *
 */

void LCD_moveCursor(uint8 row,uint8 col);

/*
 * Description :
 * Display the required string in a specified row and column index on the screen
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);

/*
 * Description :
 * Display the required decimal value on the screen
 */
void LCD_integerToString(int data);


#endif
