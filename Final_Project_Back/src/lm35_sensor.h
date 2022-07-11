 /******************************************************************************
 *
 * Module: LM35 Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: Header file for the LM35 Temperature Sensor driver
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/
#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_


#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define LM35_CHANNEL_ID         2
#define LM35_MAX_VOLT_VALUE     1.5
#define LM35_MAX_TEMPERATURE    150
#define ADC_REF_VOLT_VALUE		2.56

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Calculates temperature from ADC digital value
 *
 * Inputs: None
 *
 * Returns: Temperature value (uint8)
 *
 */
uint8 LM35_getTemperature(void);

#endif
