/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timers.c
 *
 * Description: Source file for the timer module driver for AVR microcontrollers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

/*******************************************************************************
 *                       Includes                                    		   *
 *******************************************************************************/

#include "timers.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                      Function Declarations                                  *
 *******************************************************************************/

static volatile void (*g_TIMER0_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                      ISR Declaration		                                   *
 *******************************************************************************/

ISR(TIMER0_OVF_vect) {
	(*g_TIMER0_callBackPtr)();
}

ISR(TIMER0_COMP_vect) {
	(*g_TIMER0_callBackPtr)();
}

/*******************************************************************************
 *                      Function Declarations                                  *
 *******************************************************************************/

void TIMER0_init(TIMER0_configType * config) {
	TCNT0 = config->initialValue;
	TIMSK = config->interruptMask;
	OCR0 = config->compareValue;
	TCCR0 = (config->clockSelect) | (config->compareMatchOutputMode) | (config->waveGenerationMode);
}
void TIMER0_setTimerValue(uint8 newValue) {
	TCNT0 = newValue;
}

void TIMER0_clearTimerValue(void) {
	TCNT0 = 0;
}

void TIMER0_setCallback(void (*functionPtr)(void)) {
	g_TIMER0_callBackPtr = functionPtr;
}

void TIMER0_deinit(void) {
	TCNT0 = 0;
	TIMSK &= 0xFC;
	OCR0 = 0;
	TCCR0 = 0;
}
