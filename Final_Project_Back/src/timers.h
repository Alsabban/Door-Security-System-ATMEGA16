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

/* Wave Generation Mode */
typedef enum {
	NORMAL_MODE	 = 0x00, CTC = 0x40
} TIMER0_TCCR0_WGM;

/* OC2 behavior */
typedef enum {
	OC0_DISCONNECTED = 0x00,
	TOGGLE_OC0_ON_MATCH = 0x10,
	CLEAR_OC0_ON_MATCH = 0x20,
	SET_OC0_ON_MATCH = 0x30
} TIMER0_TCCR0_COM;

/* Clock Select */
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

/* Interrupt mask */
typedef enum {
	DISABLE_INTERRUPTS = 0,
	OVERFLOW_INTERRUPT_ENABLE=0x01,
	COMPARE_MATCH_INTERRUPT_ENABLE=0x02
} TIMER0_TIMSK;

/* Configuration struct for the timer0 module */
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
/* Description:
 * Initialize the Timer0 module according to the configuration struct
 */
void TIMER0_init(TIMER0_configType* config);
/* Description:
 * Set TCNT0 value to the new value given in the parameters
 */
void TIMER0_setTimerValue(uint8 newValue);

/* Description:
 * Set TCNT0 value to 0
 */
void TIMER0_clearTimerValue(void);
/*Description:
 * Set the callback function to the function specified in the parameters
 */
void TIMER0_setCallback(void(*functionPtr)(void));

/*Description:
 * Reverse the effect done by the TIMER0_init function.
 */
void TIMER0_deinit(void);



#endif /* TIMERS_H_ */
