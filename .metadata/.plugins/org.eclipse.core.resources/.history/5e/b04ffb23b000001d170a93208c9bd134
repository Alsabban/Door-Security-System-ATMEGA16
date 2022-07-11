/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: dc_motor.c
 *
 * Description: Header file for the DC Motor driver
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/
#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"

void DcMotor_Init(void){
	/* Set defined motor pins as output pins */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN1, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN2, PIN_OUTPUT);

	/* Initially stop the motor */
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN1, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN2, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state, uint8 speed){

	/* Start the PWM module with duty cycle equal to the given speed */
	PWM_Timer0_Start(speed);

	switch (state) {

	/* Stop the motor */
	case STOP:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN1, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN2, LOGIC_LOW);
		break;

		/* Rotate Clockwise */
	case CLOCKWISE:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN1, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN2, LOGIC_LOW);
		break;

		/* Rotate Anti-clockwise */
	case ANTICLOCKWISE:
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN1, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN_IN2, LOGIC_HIGH);
	}
}
