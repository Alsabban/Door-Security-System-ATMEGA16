/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC Motor driver
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                         Definitions                                         *
 *******************************************************************************/
#define DC_MOTOR_PORT_ID            PORTB_ID

#define DC_MOTOR_PIN_IN1            PIN0_ID
#define DC_MOTOR_PIN_IN2            PIN1_ID

#define DC_MOTOR_PIN_EN1            PIN3_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum {
	CLOCKWISE, ANTICLOCKWISE, STOP
} DcMotor_State;

/*******************************************************************************
 *                         Function Prototypes                                 *
 *******************************************************************************/

/*
 * Description:
 * - The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * - Stop at the DC-Motor at the beginning through the GPIO driver.
 *
 * Inputs: None
 *
 * Returns: None
 *
 */
void DcMotor_Init(void);

/*
 * Description:
 * - The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * - Send the required duty cycle to the PWM driver based on the required speed value.
 *
 * Inputs:
 * - state: The required DC Motor state, can be CLOCKWISE, ANTICLOCKWISE, or STOP
 * - speed: decimal value for the required motor speed, must be a value from 0 -> 100
 *
 * Return: None
 *
 */
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif
