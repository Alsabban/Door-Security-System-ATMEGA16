/******************************************************************************
 *
 * Module: 
 *
 * File Name: timers.h
 *
 * Description: Header file for the timer module driver for AVR microcontrollers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#ifndef TIMERS_H_
#define TIMERS_H_

/*******************************************************************************
 *                         Includes                         	               *
 *******************************************************************************/

#include "std_types.h"

/*******************************************************************************
 *                         Definitions                                         *
 *******************************************************************************/

#define TIMER0_MAXIMUM_VALUE 255

/*******************************************************************************
 *                         Type Declarations                                   *
 *******************************************************************************/

typedef enum {
	NORMAL_MODE	 = 0x00, PWM_PHASE_CORRECT = 0x08, CTC = 0x40, FAST_PWM = 0x48
} TIMER0_TCCR0_WGM;

typedef enum {
	OC0_DISCONNECTED = 0x00,
	TOGGLE_OC0_ON_MATCH_NON_PWM = 0x10,
	CLEAR_OC0_ON_MATCH = 0x20,
	SET_OC0_ON_MATCH = 0x30
} TIMER0_TCCR0_COM;

typedef enum {
	STOP_TIMER = 0,
	FCPU_1,
	FCPU_8,
	FCPU_64,
	FCPU_256,
	FCPU_1024,
	EXTERNAL_CLOCK_FALLING_EDGE,
	EXTERNAL_CLOCK_RISING_EDGE
} TIMER0_TCCR0_CS;

typedef enum {
	DISABLE_INTERRUPTS = 0,
	OVERFLOW_INTERRUPT_ENABLE,
	COMPARE_MATCH_INTERRUPT_ENABLE
} TIMER0_TIMSK;

typedef struct {
	TIMER0_TCCR0_WGM waveGenerationMode;
	TIMER0_TCCR0_CS clockSelect;
	TIMER0_TCCR0_COM compareMatchOutputMode;
	TIMER0_TIMSK interruptMask;
	uint8 initialValue;
	uint8 compareValue;
} TIMER0_configType;

/*******************************************************************************
 *                         Function Prototypes                                 *
 *******************************************************************************/

void TIMER0_init(TIMER0_configType config);
void TIMER0_setTimerValue(uint8 newValue);
void TIMER0_clearTimerValue(void);
void TIMER0_setCallback(void(*functionPtr)(void));
void TIMER0_deinit(void);



#endif /* TIMERS_H_ */
