/*
 * LED.c
 *
 *  Created on: Oct 3, 2024
 *      Author: amr mohamed
 */

#include "LED.h"
#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"

void LEDS_init(void)
{
	/*Initializes all Leds (red, green, blue) pins direction as output pins*/
	GPIO_setupPinDirection(LED_RED_PORT_ID,LED_RED_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LED_GREEN_PORT_ID,LED_GREEN_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LED_BLUE_PORT_ID,LED_BLUE_PIN_ID, PIN_OUTPUT);

	/*checking for positive or negative logic*/
#if(LED_LOGIC == POSITIVE)

	/*turn off all the LEDs initially*/
	GPIO_writePin(LED_RED_PORT_ID, LED_RED_PIN_ID, LOGIC_LOW);
	GPIO_writePin(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LOGIC_LOW);
	GPIO_writePin(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, LOGIC_LOW);
#else

	/*turn off all the LEDs initially*/
	GPIO_writePin(LED_RED_PORT_ID, LED_RED_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, LOGIC_HIGH);
#endif
}

/*Turning the LEDs on (it happens according to the LDR's input)*/
void LED_on(LED_ID id)
{
	switch (id) {
	case LED_RED:
#if(LED_LOGIC == POSITIVE)
		GPIO_writePin(LED_RED_PORT_ID, LED_RED_PIN_ID, LOGIC_HIGH);
#else
		GPIO_writePin(LED_RED_PORT_ID, LED_RED_PIN_ID, LOGIC_LOW);
#endif
		break;


	case LED_GREEN:
#if(LED_LOGIC == POSITIVE)
		GPIO_writePin(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LOGIC_HIGH);
#else
		GPIO_writePin(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LOGIC_LOW);
#endif
		break;


	case LED_BLUE:
#if(LED_LOGIC == POSITIVE)
		GPIO_writePin(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, LOGIC_HIGH);
#else
		GPIO_writePin(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, LOGIC_LOW);
#endif
		break;
	}

}

/*Turning the LEDs off (it happens according to the LDR's input)*/
void LED_off(LED_ID id)
{
	switch (id) {
	case LED_RED:
#if(LED_LOGIC == POSITIVE)
		GPIO_writePin(LED_RED_PORT_ID, LED_RED_PIN_ID, LOGIC_LOW);
#else
		GPIO_writePin(LED_RED_PORT_ID, LED_RED_PIN_ID, LOGIC_HIGH);
#endif
		break;


	case LED_GREEN:
#if(LED_LOGIC == POSITIVE)
		GPIO_writePin(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LOGIC_LOW);
#else
		GPIO_writePin(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LOGIC_HIGH);
#endif
		break;


	case LED_BLUE:
#if(LED_LOGIC == POSITIVE)
		GPIO_writePin(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, LOGIC_LOW);
#else
		GPIO_writePin(LED_BLUE_PORT_ID, LED_BLUE_PIN_ID, LOGIC_HIGH);
#endif
		break;
	}

}
