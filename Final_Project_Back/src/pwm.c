 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: Source file for the PWM module driver for AVR microcontrollers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#include "pwm.h"
#include <avr/io.h> /* to access timer0 registers */
#include "gpio.h" /* to set PB3/OC0 as an output pin */



void PWM_Timer0_Start(uint8 duty_cycle){

	/* Set counter to 0 */
	TCNT0=0;

	/* set PB3/OC0 as an output pin */
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

	/* OCR0 value = (percentage of duty cycle/100)* (maximum register value = 255) */
	OCR0=(uint8)(((float)duty_cycle/100)*255);

	/* Timer/Counter Control Register:
	 * 1- Set mode as Fast PWM mode -> WGM00 and WGM01 = 1
	 * 2- Non-Inverting mode -> COM01 = 1
	 * 3- F_CPU/8 Prescalar -> PRESCALAR8 defined as 2 -> CS00 and CS02 =0, CS01=1
	 */
	TCCR0=FAST_PWM_MODE|NON_INVERTING_MODE|PRESCALAR_8;

}
