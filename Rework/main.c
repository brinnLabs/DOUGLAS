/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F24K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include "mcc_generated_files/mcc.h"
//#include "stepper.h"
#include <time.h>

#define MIN_STEP_SPEED 50 //minimal speed;
#define PI       3.14159265358979323846
#define RAD_TO_DEG (180.0/PI)
#define DEG_TO_RAD (PI/180.0)

//Steppers are 1.8 degree steps, 200 steps per revolution, modified half step turns it to 400 steps per revolution
//each revolution is about 5 inches of string so we should max out at about 1600 steps, it is ok to level out at 800 
//the steppers should move to the starting angle and move in relation to that. 

/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    //set a random angle to start in
    srand(ADC_GetConversionResult());
    float startingAngle1 = rand() % 360;
    float startingAngle2 = rand() % 360;

    //where do the motors need to begin? how many steps in which direction?
    int initStep1Steps = sin(startingAngle1 * DEG_TO_RAD)* 800;
    int initStep2Steps = sin(startingAngle2 * DEG_TO_RAD)* 800;

    unsigned long currentStep1 = startingAngle1;
    unsigned long currentStep2 = startingAngle2;

    //we need a timer because this will execute too fast and the motors will slip so we need a short delay
    TMR3_WriteTimer(40);
    TMR5_WriteTimer(40);
    TMR3_StartTimer();
    TMR5_StartTimer();

    while (abs(initStep1Steps) + abs(initStep2Steps) > 0) {
        //has the time interval been met
        if (TMR3_HasOverflowOccured()) {
            //check if the motor has steps left
            if (abs(initStep1Steps) > 0) {
                stepper1Step(initStep1Steps > 0 ? true : false);
                initStep1Steps > 0 ? initStep1Steps-- : initStep1Steps++;
            }
            if (abs(initStep2Steps) > 0) {
                stepper2Step(initStep2Steps > 0 ? true : false);
                initStep2Steps > 0 ? initStep2Steps-- : initStep2Steps++;
            }
            //reload the delay
            TMR3_Reload();
        }
    }


    //the steppers should be in the correct location now so lets just ran the normal script
    while (1) {
        //to estimate the delay we want steps * 180 degrees (half a cycle) 
        // speed is fastest between peaks at 90 and 270 degrees or pi/2 3pi/2
        //we will use timer 3 for stepper 1 and timer 5 for stepper 2
        if (TMR3_HasOverflowOccured()) {
            //delay for next step is slowest at peaks so when angle = 90 our speed should be about 150ms per delay
            float currentAngle1 = sin(DEG_TO_RAD * (360 * (++currentStep1 / 1600.0)));
            stepper1Step(currentAngle1 > 0 ? true : false);
            float timert = 100.0 * (currentAngle1 >= 0 ? currentAngle1 : currentAngle1 *-1);
            TMR3_WriteTimer(MIN_STEP_SPEED + timert);
            TMR3_StartTimer();
        }
        if (TMR5_HasOverflowOccured()) { 
            //delay for next step is slowest at peaks so when angle = 90 our speed should be about 150ms per delay
            float currentAngle2 = sin(DEG_TO_RAD * (360 * (++currentStep2 / 1600.0)));
            stepper2Step(currentAngle2 > 0 ? true : false);
            float timert = 100.0 * (currentAngle2 >= 0 ? currentAngle2 : currentAngle2 *-1);
            TMR5_WriteTimer(MIN_STEP_SPEED + timert);
            TMR5_StartTimer();
        }

    }
}
/**
 End of File
 */