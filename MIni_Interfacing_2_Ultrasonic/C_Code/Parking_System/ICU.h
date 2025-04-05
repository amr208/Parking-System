/*
 * ICU.h
 *
 *  Created on: Oct 11, 2024
 *      Author: amr mohamed
 */

#ifndef MCAL_ICU_H_
#define MCAL_ICU_H_

#include "std_types.h"

/*******************************************************************************
 *                              Definitions		                               *
 *******************************************************************************/
/* Macro to define the Force Output Compare for Timer1 Channel A in Normal Mode*/
#define ICU_TIMER1_NORMALMODE_FOC1A FOC1A

/* Macro to define the Force Output Compare for Timer1 Channel B in Normal Mode*/
#define ICU_TIMER1_NORMALMODE_FOC1B FOC1B

/* Macro to enable the Timer1 Input Capture Interrupt*/
#define ICU_TIMER1_INTERRUPT_ENABLE TICIE1

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* Enumeration for the edge type of the ICU (Input Capture Unit)*/
typedef enum
{
    FALLING, // Falling edge trigger
    RISING   // Rising edge trigger
} ICU_Edge;

/* Enumeration for the clock source of the ICU*/
typedef enum {
    NO_CLOCK,    // No clock source
    F_CPU_CLOCK, // CPU clock
    F_CPU_8,     // CPU clock divided by 8
    F_CPU_64,    // CPU clock divided by 64
    F_CPU_256,   // CPU clock divided by 256
    F_CPU_1024   // CPU clock divided by 1024
} ICU_CPU_Clocks;

/* Structure to configure the ICU*/
typedef struct  {
    ICU_Edge edge;          // Edge type for triggering the ICU
    ICU_CPU_Clocks clock;   // Clock source for the ICU
} ICU_Configuration;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/**
 * Description : Function to initialize the ICU driver
 *  1. Set the required clock.
 *  2. Set the required edge detection.
 *  3. Enable the Input Capture Interrupt.
 *  4. Initialize Timer1 Registers.
 */
void ICU_Init(const ICU_Configuration * Config_Ptr);

/**
 * Description : Function to set the callback function for the ICU ISR
 *  1. Store the address of the callback function.
 *  2. The callback function will be called by the ISR.
 */
void ICU_SetCallBack(void (*CallBackPtrToFunc) (void));

/**
 * Description : Function to set the edge detection type for the ICU
 *  1. Set the edge detection type (FALLING or RISING).
 *  2. Update the corresponding register.
 */
void ICU_setEdgeDetectionType(const ICU_Edge edgeType);

/**
 * Description : Function to get the current value captured by the ICU
 *  1. Read the value from the input capture register.
 *  2. Return the captured value.
 */
uint16 ICU_getInputCaptureValue(void);

/**
 * Description : Function to clear the timer value of the ICU
 *  1. Reset the timer register to zero.
 */
void ICU_clearTimerValue(void);

/**
 * Description : Function to deinitialize the ICU
 *  1. Disable the ICU.
 *  2. Reset the configuration to default.
 */
void ICU_deInit(void);

#endif /* MCAL_ICU_H_ */
