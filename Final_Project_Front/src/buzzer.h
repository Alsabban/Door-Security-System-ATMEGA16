/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: header file for buzzers
 *
 * Author: Youssef Alsabban
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include"std_types.h"
#include"gpio.h"
#include"common_macros.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_PORT_ID PORTD_ID
#define BUZZER_PIN PIN7_ID

/*******************************************************************************
 *							function Declaration							   *
 ******************************************************************************/
/* Set the buzzer pin as an output pin */
void BUZZER_init(void);
/* Turn buzzer on by setting pin to 1 */
void BUZZER_on(void);
/* Turn buzzer off by setting pin to 0 */
void BUZZER_off(void);




#endif /* BUZZER_H_ */
