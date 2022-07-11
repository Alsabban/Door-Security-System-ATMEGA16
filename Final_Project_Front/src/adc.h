/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.h
 *
 * Description: header file for the ADC module driver for AVR microcontrollers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "std_types.h"
#include <avr/io.h>


/*******************************************************************************
 *                         Definitions                                         *
 *******************************************************************************/

#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * Description:
 * Adjusts reference voltage
 * -AREF: internal vref off
 * -AVCC: AVCC with external capacitor at AREF pin
 * -INTERNAL: Internal 2.56V Voltage Reference with external capacitor at AREF pin
 */
typedef enum {
	AREF = 0x00,
	AVCC = 0x40,
	INTERNAL_VREF = 0xC0
} ADC_ADMUX_REFS;

/*
 * Description :
 * Adjust data alignment in the ADC data register ADLAR=1 -> Left , ADLAR=0 -> Right
 *
 */
typedef enum {
	RIGHT = 0x00,
	LEFT = 0x20
} ADC_ADMUX_ADLAR;

/*
 * Description :
 * ADC Enable Bit
 *
 */
typedef enum {
	ADC_DISABLE,
	ADC_ENABLE = 0x80
} ADC_ADCSRA_ADEN;

/*
 * Description :
 * ADC prescaler selection
 *
 */
typedef enum {
	FCPU_2 = 1,
	FCPU_4,
	FCPU_8,
	FCPU_16,
	FCPU_32,
	FCPU_64,
	FCPU_128
} ADC_ADCSRA_ADPS;

/*
 * Description :
 * ADC interrupt enable bit selection
 *
 */
typedef enum {
	INT_DISABLE = 0x00,
	INT_ENABLE = 0x08
} ADC_ADCSRA_ADIE;

/*
 * Description :
 * Auto-Trigger enable bit selection
 *
 */
typedef enum {
	AUTOTRIGGER_DISABLE,
	AUTOTRIGGER_ENABLE = 0x20
} ADC_ADCSRA_ADATE;

/*
 * Description :
 * Auto-Trigger source selection
 *
 */
typedef enum {
	FREE_RUNNING,
	ANALOG_COMPARATOR = 0x20,
	EXTERNAL_INT0 = 0x40,
	TIMER0_CMP = 0x60,
	TIMER0_OVF = 0x80,
	TIMER1B_CMP = 0xA0,
	TIMER1_OVF = 0xC0,
	TIMER1_CAPTURE = 0xE0
} ADC_SFIOR_ADTS;

/* Description:
 * Configuration Structure for initialization. Pass the structure by reference giving values using
 * previously defined enums.
 *
 */
typedef struct {
	ADC_ADMUX_REFS ref_volt;
	ADC_ADMUX_ADLAR data_adjust;
	ADC_ADCSRA_ADEN adc_enable;
	ADC_ADCSRA_ADPS prescaler;
	ADC_ADCSRA_ADIE interrupt_enable;
	ADC_ADCSRA_ADATE autoTrigger_enable;
	ADC_SFIOR_ADTS autoTrigger_source;
} ADC_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Initializes the ADC module according to the ADC_ConfigType struct given */
void ADC_init(ADC_ConfigType * config);

/* Reads from given channel and returns digital value */
uint16 ADC_readChannel(uint8 ch_num);

#endif
