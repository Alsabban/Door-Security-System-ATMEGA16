 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/
#include "external_eeprom.h"
#include "i2c.h"

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
    I2C_start();
    if (I2C_getStatus() != I2C_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    I2C_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (I2C_getStatus() != I2C_MT_SLA_W_ACK)
        return ERROR; 
		 
    /* Send the required memory location address */
    I2C_writeByte((uint8)(u16addr));
    if (I2C_getStatus() != I2C_MT_DATA_ACK)
        return ERROR;
		
    /* write byte to eeprom */
    I2C_writeByte(u8data);
    if (I2C_getStatus() != I2C_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    I2C_stop();
	
    return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
    I2C_start();
    if (I2C_getStatus() != I2C_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    I2C_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (I2C_getStatus() != I2C_MT_SLA_W_ACK)
        return ERROR;
		
    /* Send the required memory location address */
    I2C_writeByte((uint8)(u16addr));
    if (I2C_getStatus() != I2C_MT_DATA_ACK)
        return ERROR;
		
    /* Send the Repeated Start Bit */
    I2C_start();
    if (I2C_getStatus() != I2C_REP_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    I2C_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (I2C_getStatus() != I2C_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = I2C_readByteWithNACK();
    if (I2C_getStatus() != I2C_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    I2C_stop();

    return SUCCESS;
}
