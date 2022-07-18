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
#include "external_eeprom.h"

/*******************************************************************************
 *                      Functions Definition                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data)
{
	/* Send the Start Bit */
	I2C_start();
	if (I2C_getStatus() != I2C_START)
		return ERROR;

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write)
	 * EEPROM memory was set up as fixed address beginning with 0xA0
	 * 11 bit address for memory location divides 3bits and 8 to avoid sending 2bytes for memory addressing
	 * (Fixed 1010+ 3 MSB bits + R/W-)(the 8 LSB bits in memory address)
	 */
	I2C_writeByte(0xA0 | (uint8)((u16addr&0x0700)>>7));
	if (I2C_getStatus() != I2C_MT_SLA_W_ACK)
		return ERROR;
	/* Send the required memory location address */
	I2C_writeByte((uint8)(u16addr & 0x00FF));
	if (I2C_getStatus() != I2C_MT_DATA_ACK)
		return ERROR;

	/* write byte to EEPROM */
	I2C_writeByte(u8data);
	if (I2C_getStatus() != I2C_MT_DATA_ACK)
		return ERROR;
	/* Send the Stop Bit */
	I2C_stop();
	/*return success*/
	return SUCCESS;
}



uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data)
{
	/* Send the Start Bit */
	I2C_start();
	if (I2C_getStatus() != I2C_START)
		return ERROR;
	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=1 (write)
	 * EEPROM memory was set up as fixed address beginning with 0xA0
	 * 11 bit address for memory location divides 3bits and 8 to avoid sending 2bytes for memory addressing
	 * (Fixed 1010+ 3 MSB bits + R/W-)(the 8 LSB bits in memory address)
	 */
	I2C_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
	if (I2C_getStatus() != I2C_MT_SLA_W_ACK)
		return ERROR;
	/* Send the required memory location address */
	I2C_writeByte((uint8)(u16addr & 0x00FF));
	if (I2C_getStatus() != I2C_MT_DATA_ACK)
		return ERROR;
	/***********************Repeat start*************************/
	I2C_start();
	if (I2C_getStatus() != I2C_REP_START)
		return ERROR;
	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=0 (write)
	 * EEPROM memory was set up as fixed address beginning with 0xA0
	 * 11 bit address for memory location divides 3bits and 8 to avoid sending 2bytes for memory addressing
	 * (Fixed 1010+ 3 MSB bits + R/W-)(the 8 LSB bits in memory address)
	 */

	/* Send the device address, we need to get A8 A9 A10 address bits from the
	 * memory location address and R/W=1 (Read) */

	I2C_writeByte(0xA0 | 0x01);
	if (I2C_getStatus() != I2C_MT_SLA_R_ACK)
		return ERROR;

	/* Read Byte from Memory without send ACK */
	*u8data = I2C_readByteWithNACK();
	if (I2C_getStatus() != I2C_MR_DATA_NACK)
		return ERROR;

	/* Send the Stop Bit */
	I2C_stop();
	/*return success*/
	return SUCCESS;
}
