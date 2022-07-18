/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for buzzers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/
#include "std_types.h"
#include "buzzer.h"
#include "gpio.h"

/*******************************************************************************
 *							function Definition							   *
 ******************************************************************************/
void BUZZER_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN, LOGIC_LOW);

}
void BUZZER_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN, LOGIC_HIGH);
}
void BUZZER_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN, LOGIC_LOW);
}
