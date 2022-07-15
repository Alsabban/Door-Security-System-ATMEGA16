/******************************************************************************
 *
 * Module: I2C
 *
 * File Name: i2c.h
 *
 * Description: header file for the I2C module driver for AVR microcontrollers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/

#ifndef I2C_H_
#define I2C_H_

/*******************************************************************************
 *                     		Includes		                                   *
 *******************************************************************************/

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define I2C_START         0x08 /* start has been sent */
#define I2C_REP_START     0x10 /* repeated start */
#define I2C_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define I2C_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define I2C_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define I2C_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define I2C_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum {
	I2C_INT_DISABLE = 0x00, I2C_INT_ENABLE = 0x01
} I2C_TWCR_TWIE;

typedef enum {
	I2C_ENABLE = 0x04, I2C_DISABLE = 0x00
} I2C_TWCR_TWEN;

typedef enum {
	PRESCALER_1 = 0x00,
	PRESCALER_4 = 0x01,
	PRESCALER_16 = 0x02,
	PRESCALER_64 = 0x03
} I2C_TWSR_TWPS;

typedef struct {
	char brValue;
	I2C_TWSR_TWPS prescaler;
	char address;
	I2C_TWCR_TWEN enable;
	I2C_TWCR_TWIE int_enable;
} I2C_configType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void I2C_init(I2C_configType *configs);
void I2C_start(void);
void I2C_stop(void);
void I2C_writeByte(uint8 data);
uint8 I2C_readByteWithACK(void);
uint8 I2C_readByteWithNACK(void);
uint8 I2C_getStatus(void);

#endif
