/*
 * Main_App.c
 *
 *  Created on: Oct 11, 2024
 *      Author: amr mohamed
 */

#include "LCD.h"
#include "buzzer.h"
#include "LED.h"
#include "ICU.h"
#include "US_Sensor.h"
#include "std_types.h"
#include <util/delay.h>
#include "common_macros.h"
#include <avr/io.h> /* To use the SREG register */

uint8 g_edgeCount = 0;  /* Global variable to count the number of edges detected */
uint16 g_timePeriod = 0;   /* Global variable to store the time period between edges */

void Ultrasonic_edgeProcessing(void)
{
	/* Increment the edge count, which make sense,
	 * since we call this function after a first edge detection
	 */
    g_edgeCount++;

    if(g_edgeCount == 1)
    {
        ICU_clearTimerValue();  /* Clear the timer value at the first edge */
        ICU_setEdgeDetectionType(FALLING);  /* Set edge detection to falling edge */
    }
    else if(g_edgeCount == 2)
    {
        g_timePeriod = ICU_getInputCaptureValue();  /* Capture the timer value at the second edge */
        ICU_setEdgeDetectionType(RISING);  /* Set edge detection back to rising edge */
    }
}


int main(void)
{
	uint16 distance = 0;
	Ultrasonic_init();  /* Initialize the ultrasonic sensor */
	SREG |= (1<<7);  /* Enable Global Interrupt I-Bit */
	Buzzer_init();  /* Initialize the buzzer */
	LCD_init();  /* Initialize the LCD display */
	LEDS_init();  /* Initialize the LEDs */
/*************************************************************/

	Ultrasonic_Trigger();
	while(1)/*Main program scan cycle*/
	{
		/**
		 * This section handles the measurement of distance using the ultrasonic sensor
		 * and displays the result on the LCD.
		 */
		if(g_edgeCount == 2)  /** Check if the edge count is 2 */
		{
		    distance = Ultrasonic_readDistance();  /** Read the distance from the ultrasonic sensor */
		    LCD_MoveCursor(0,0);  /** Move the LCD cursor to the beginning of the first line */
		    LCD_SendString("Distance = ");
		    if(distance < 100)
		    {
		        LCD_intgerToString(distance);  /** Display the distance on the LCD */
		        LCD_SendString(" ");  /** Add a space for formatting */
		    }
		    else if (distance < 10)
			{
				LCD_intgerToString(distance); /** Display the distance on the LCD */
				LCD_SendString("  "); /** Add a space for formatting */
			}

		    else
		    {
		        LCD_intgerToString(distance);  /** Display the distance on the LCD */
		    }
		    LCD_MoveCursor(0,14);
		    LCD_SendString("cm");  /** Display the unit 'cm' */
		    g_edgeCount = 0;  /** Reset edge count for the next measurement cycle */
		    Ultrasonic_Trigger();
		}
/************************************************************************************************/
		/**
		 * This section controls the LEDs and buzzer based on the measured distance.
		 * Different distance ranges trigger different LED and buzzer behaviors.
		 */

		if(distance >= 20)  /** If the distance is 20 cm or more */
		{
		    LED_off(LED_RED);  /** Turn off the red LED */
		    LED_off(LED_GREEN);  /** Turn off the green LED */
		    LED_off(LED_BLUE);  /** Turn off the blue LED */
		    Buzzer_off();  /** Turn off the buzzer */
		    LCD_MoveCursor(1,6);  /** Move the LCD cursor to the second line, fifth position */
		    LCD_SendString("    ");  /** Remove STOP from the LCD */
		}
		else if (distance >= 16 && distance < 20)  /** If the distance is between 16 cm and 20 cm */
		{
		    LED_on(LED_RED);  /** Turn on the red LED */
		    LED_off(LED_GREEN);  /** Turn off the green LED */
		    LED_off(LED_BLUE);  /** Turn off the blue LED */
		    Buzzer_off();  /** Turn off the buzzer */
		    LCD_MoveCursor(1,6);  /** Move the LCD cursor to the second line, fifth position */
		    LCD_SendString("    ");  /** Remove STOP from the LCD */
		}
		else if (distance >= 11 && distance < 16)  /** If the distance is between 11 cm and 16 cm */
		{
		    LED_on(LED_RED);  /** Turn on the red LED */
		    LED_on(LED_GREEN);  /** Turn on the green LED */
		    LED_off(LED_BLUE);  /** Turn off the blue LED */
		    Buzzer_off();  /** Turn off the buzzer */
		    LCD_MoveCursor(1,6);  /** Move the LCD cursor to the second line, fifth position */
		    LCD_SendString("    ");  /** Remove STOP from the LCD */
		}
		else if (distance >= 6 && distance < 11)  /** If the distance is between 6 cm and 11 cm */
		{
		    LED_on(LED_RED);  /** Turn on the red LED */
		    LED_on(LED_GREEN);  /** Turn on the green LED */
		    LED_on(LED_BLUE);  /** Turn on the blue LED */
		    Buzzer_off();  /** Turn off the buzzer */
		    LCD_MoveCursor(1,6);  /** Move the LCD cursor to the second line, fifth position */
		    LCD_SendString("    ");  /** Remove STOP from the LCD */
		}
		else if (distance <= 5)  /** If the distance is 5 cm or less */
		{
		    LED_on(LED_RED);  /** Turn on the red LED */
		    LED_on(LED_GREEN);  /** Turn on the green LED */
		    LED_on(LED_BLUE);  /** Turn on the blue LED */
		    _delay_ms(500);  /** Wait for 500 milliseconds */
		    LED_off(LED_RED);  /** Turn off the red LED */
		    LED_off(LED_GREEN);  /** Turn off the green LED */
		    LED_off(LED_BLUE);  /** Turn off the blue LED */
		    _delay_ms(500);  /** Wait for 500 milliseconds */
		    Buzzer_on();  /** Turn on the buzzer */
		    LCD_MoveCursor(1,6);  /** Move the LCD cursor to the second line, fifth position */
		    LCD_SendString("STOP");  /** Display "STOP" on the LCD */
		}
	}
}
