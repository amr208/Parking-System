/*
 * LED.h
 *
 *  Created on: Oct 3, 2024
 *      Author: amr mohamed
 */

#ifndef LED_H_
#define LED_H_

#include "gpio.h"
#include "std_types.h"

/*******************************************************************************
 *                             Data Types Declarations                         *
 *******************************************************************************/

/*enumeration used for the ease of using words*/
typedef enum
{
    LED_RED,
    LED_GREEN,
    LED_BLUE
} LED_ID;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*defining which logic are we work with (Positive or Negative)*/
#define LED_LOGIC				POSITIVE
#define POSITIVE				1
#define NEGATIVE				0

/*LEDs Pins and Ports*/
#define LED_RED_PORT_ID			PORTC_ID
#define LED_RED_PIN_ID			PIN0_ID
#define LED_GREEN_PORT_ID		PORTC_ID
#define LED_GREEN_PIN_ID		PIN1_ID
#define LED_BLUE_PORT_ID		PORTC_ID
#define LED_BLUE_PIN_ID			PIN2_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/*initial configuration for LEDs*/
void LEDS_init(void);

/*Turn a specific led on*/
void LED_on(LED_ID id);

/*Turn a specific led off*/
void LED_off(LED_ID id);


#endif /* LED_H_ */
