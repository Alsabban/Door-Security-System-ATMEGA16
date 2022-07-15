#include "timers.h"
#include <avr/io.h>
void main(void){
	TIMER0_configType config={
			CTC,
			FCPU_1024,
			TOGGLE_OC0_ON_MATCH_NON_PWM,
			DISABLE_INTERRUPTS,
			0,
			255
	};
	DDRB=255;
	TIMER0_init(config);
	while(1);
}
