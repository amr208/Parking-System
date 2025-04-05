/*
 * US_Sensor.c
 *
 *  Created on: Oct 11, 2024
 *      Author: amr mohamed
 */
#include "std_types.h"
#include "US_Sensor.h"
#include "ICU.h"
#include <util/delay.h>

extern uint16 g_timePeriod;
/**
 * Initializes the ultrasonic sensor.
 * This function sets up the ICU (Input Capture Unit) with the specified configuration,
 * sets the callback function for edge processing, and configures the GPIO pins for the
 * trigger and echo pins of the ultrasonic sensor.
 */
void Ultrasonic_init(void)
{
	ICU_Configuration Ultrasonic_config = {RISING, F_CPU_8}; /** Configure ICU to capture on rising edge with a prescaler of 8 */
	ICU_Init(&Ultrasonic_config); /** Initialize the ICU with the given configuration */
	ICU_SetCallBack(Ultrasonic_edgeProcessing); /** Set the callback function for edge processing */
	GPIO_setupPinDirection(US_TRIG_PORT, US_TRIG_PIN, PIN_OUTPUT); /** Set the trigger pin as output */
	GPIO_setupPinDirection(US_ECHO_PORT, US_ECHO_PIN, PIN_INPUT); /** Set the echo pin as input */

}

/**
 * Triggers the ultrasonic sensor to send a pulse.
 * This function sends a high pulse of 10 microseconds to the trigger pin of the ultrasonic sensor.
 */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(US_TRIG_PORT, US_TRIG_PIN, LOGIC_HIGH); /** Set the trigger pin high */
	_delay_us(10); /** Wait for 10 microseconds */
	GPIO_writePin(US_TRIG_PORT, US_TRIG_PIN, LOGIC_LOW); /** Set the trigger pin low */
}

/**
 * Reads the distance measured by the ultrasonic sensor.
 * @return The distance measured by the ultrasonic sensor in centimeters.
 * This function triggers the ultrasonic sensor, waits for the echo response, and calculates the distance
 * based on the timer value and the speed of sound.
 */
uint16 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger(); /** Trigger the ultrasonic sensor */
	uint16 distance;
	distance = (uint16)((float32)(g_timePeriod /112)); /** Calculate the distance based on the timer value */
	return distance; /** Return the calculated distance */
}
