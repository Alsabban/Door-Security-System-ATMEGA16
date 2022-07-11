/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the PWM module driver for AVR microcontrollers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#include "adc.h"
#include "common_macros.h"
#include "std_types.h"
#include <avr/io.h>


void ADC_init(ADC_ConfigType * config){
	/* Pass each struct value to its corresponding register */
	ADMUX= (config->ref_volt)|(config->data_adjust);
	ADCSRA=(config->adc_enable|config->autoTrigger_enable)|(config->interrupt_enable)|(config->prescaler);
	SFIOR=(config->autoTrigger_source);
}

uint16 ADC_readChannel(uint8 ch_num){
	/* Disregard any bit after bit 3 */
	ch_num&=0x0E;
	/* Clear bits 0->3 */
	ADMUX&=0xE0;
	/* Insert channel number */
	ADMUX|=ch_num;
	/* Start conversion */
	SET_BIT(ADCSRA,ADSC);
	/* Polling interrupt flag */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	/* Clear interrupt flag */
	SET_BIT(ADCSRA,ADIF);
	/* return data register */
	return ADC;
}
