#include "i2c.h"
#include "common_macros.h"
#include "std_types.h"
#include <avr/io.h>

void I2C_init(void) {
	SET_BIT(TWCR, TWEN);
	TWBR = 2;
	TWSR = 0;
	TWAR = (0x01 << 1);
}

void TWI_start(void) {
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT));
}


void I2C_stop(void){
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}



void I2C_writeByte(uint8 data){
	TWDR=data;
	TWCR=(1<TWINT)|(1<<TWEN);
}

uint8 I2C_getStatus(void){
	uint8 status= TWSR|0xF8;
	return status;
}
