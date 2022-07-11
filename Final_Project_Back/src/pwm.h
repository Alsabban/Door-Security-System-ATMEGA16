/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for the PWM module driver for AVR microcontrollers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                         Definitions                                         *
 *******************************************************************************/
#define FAST_PWM_MODE (1<<WGM00)|(1<<WGM01)
#define NON_INVERTING_MODE (1<<COM01)
#define PRESCALAR_1 1
#define PRESCALAR_8 2
#define PRESCALAR_64 3
#define PRESCALAR_256 4
#define PRESCALAR_1024 5

/*******************************************************************************
 *                         Function Prototypes                                 *
 *******************************************************************************/

/*
 *  Description:
 * - The function responsible for trigger the Timer0 with the PWM Mode.
 *
 * - Setup the PWM mode with Non-Inverting.
 *
 * - Setup the prescaler with F_CPU/8.
 *
 * - Setup the compare value based on the required input duty cycle
 *
 * - Setup the direction for OC0 as output pin through the GPIO driver.
 *
 * - The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 *
 *
 *  Inputs:
 * - duty_cycle: The required duty cycle percentage of the generated PWM signal.
 *   Its value should be from 0 → 100
 *
 *
 *  Return: None
 *
 */

void PWM_Timer0_Start(uint8 duty_cycle);

#endif
