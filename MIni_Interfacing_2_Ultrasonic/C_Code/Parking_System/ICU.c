/*
 * ICU.c
 *
 *  Created on: Oct 11, 2024
 *      Author: amr mohamed
 */

#include "icu.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */
#include "gpio.h"



/**
 * Static volatile pointer to function (callback)
 *  1. Initialized to NULL_PTR.
 *  2. Used to store the address of the callback function.
 */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/**
 * 	ISR for Timer1 Capture Event
 *  1. Check if the callback pointer is not NULL.
 *  2. If not NULL, call the callback function.
 */
ISR(TIMER1_CAPT_vect)
{
    if(g_callBackPtr != NULL_PTR)
    {
        /** Call the callback function */
        (*g_callBackPtr)();
    }
}

void ICU_Init(const ICU_Configuration * Config_Ptr)
{
		/** Set PD6 (Input Capture Pin) as input */
	    GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);

	    /** Force Output Compare for Timer1 Channel A in Normal Mode */
	    SET_BIT(TCCR1A, ICU_TIMER1_NORMALMODE_FOC1A);

	    /** Force Output Compare for Timer1 Channel B in Normal Mode */
	    SET_BIT(TCCR1A, ICU_TIMER1_NORMALMODE_FOC1B);

	    /** Set the clock source for Timer1 */
	    TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock);

	    /** Set the edge detection type for the ICU */
	    TCCR1B = (TCCR1B & 0xBF) | ((Config_Ptr->edge) << 6);

	    /** Initialize Timer1 counter to 0 */
	    TCNT1 = 0;

	    /** Initialize Input Capture Register to 0 */
	    ICR1 = 0;

	    /** Enable the Input Capture Interrupt */
	    SET_BIT(TIMSK, ICU_TIMER1_INTERRUPT_ENABLE);
}


/**
 * Description : Function to set the callback function for the ICU ISR
 *  1. Store the address of the callback function.
 *  2. The callback function will be called by the ISR.
 */
void ICU_SetCallBack(void (*CallBackPtrToFunc) (void))
{
    /** Store the address of the callback function */
    g_callBackPtr = CallBackPtrToFunc;
}

/**
 * Description : Function to set the edge detection type for the ICU
 *  1. Set the edge detection type (FALLING or RISING).
 *  2. Update the corresponding register.
 */
void ICU_setEdgeDetectionType(const ICU_Edge edgeType)
{
    /** Set the edge detection type in the TCCR1B register */
    TCCR1B = (TCCR1B & 0xBF) | (edgeType << 6);
}

/**
 * Description : Function to get the current value captured by the ICU
 *  1. Read the value from the input capture register.
 *  2. Return the captured value.
 */
uint16 ICU_getInputCaptureValue(void)
{
    /** Return the value from the Input Capture Register (ICR1) */
    return ICR1;
}

/**
 * Description : Function to clear the timer value of the ICU
 *  1. Reset the timer register to zero.
 */
void ICU_clearTimerValue(void)
{
    /** Clear the Timer1 counter register */
    TCNT1 = 0;
}

/**
 * Description : Function to deinitialize the ICU
 *  1. Disable the ICU.
 *  2. Reset the configuration to default.
 */
void ICU_deInit(void)
{
    /** Reset Timer1 Control Register A */
    TCCR1A = 0;

    /** Reset Timer1 Control Register B */
    TCCR1B = 0;

    /** Clear the Timer1 counter register */
    TCNT1 = 0;

    /** Clear the Input Capture Register */
    ICR1 = 0;

    /** Disable the Input Capture Interrupt */
    CLEAR_BIT(TIMSK, TICIE1);

    /** Reset the callback pointer to NULL */
    g_callBackPtr = NULL_PTR;
}


