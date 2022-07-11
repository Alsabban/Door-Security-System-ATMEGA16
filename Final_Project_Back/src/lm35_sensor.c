 /******************************************************************************
 *
 * Module: LM35 Temperature Sensor
 *
 * File Name: lm35_sensor.c
 *
 * Description: Source file for the LM35 Temperature Sensor driver
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#include "lm35_sensor.h"

#include "adc.h" /* To get digital value from ADC channel */

uint8 LM35_getTemperature(void)
{
	uint8 temp_value;

	uint16 adc_value;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(LM35_CHANNEL_ID);

	/* Calculate the temperature from the ADC value = (sensor maximum temperature * ADC reference volt)/(ADC maximum value * Sensor Maximum voltage */
	temp_value = (uint8)(((uint32)adc_value*LM35_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*LM35_MAX_VOLT_VALUE));

	return temp_value;
}

