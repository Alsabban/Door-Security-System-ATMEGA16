/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.c
 *
 * Description: Source file for the I2C module driver for AVR microcontrollers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#include "i2c.h"
#include "common_macros.h"
#include "std_types.h"
#include <avr/io.h>


void I2C_init(I2C_configType *configs) {
	TWBR = (configs->brValue);
	TWSR = (configs->prescaler);
	TWAR = ((configs->address) << 1);
	TWCR = (configs->enable) | (configs->int_enable);
}

void I2C_start(void) {
	TWCR |= (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
}

void I2C_stop(void) {
	TWCR |= (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void I2C_writeByte(uint8 data) {
	TWDR = data;
	TWCR |= (1 < TWINT) | (1 << TWEN);
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
}

uint8 I2C_readByteWithACK(void) {
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR |= (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	/* Read Data */
	return TWDR;
}

uint8 I2C_readByteWithNACK(void) {
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR |= (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	/* Read Data */
	return TWDR;
}

uint8 I2C_getStatus(void) {
	uint8 status = TWSR & 0xF8;
	return status;
}
