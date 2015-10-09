/**
  TMR3 Generated Driver File

  @Company
	Microchip Technology Inc.

  @File Name
	tmr3.c

  @Summary
	This is the generated driver implementation file for the TMR3 driver using MPLAB® Code Configurator

  @Description
	This source file provides APIs for TMR3.
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

  /**
	Section: Included Files
   */

#include <xc.h>
#include "tmr3.h"

   /**
	 Section: Global Variable Definitions
	*/
volatile uint16_t timer3ReloadVal;

/**
  Section: TMR3 APIs
 */

void TMR3_Initialize(void) {
	//Set the Timer to the options selected in the GUI

	//T3RD16 disabled; TMR3CS FOSC/4; T3CKPS 1:1; nT3SYNC synchronize; TMR3ON disabled; T3OSCEN disabled; 
	T3CON = 0x00;

	//T3GTM disabled; T3GPOL low; T3GGO done; T3GVAL disabled; T3GSPM disabled; TMR3GE disabled; T3GSS T3G; 
	T3GCON = 0x00;

	//TMR3H 0; 
	TMR3H = 0x00;

	//TMR3L 0; 
	TMR3L = 0x00;

	// Load the TMR value to reload variable
	timer3ReloadVal = TMR3;

	// Clearing IF flag.
	PIR2bits.TMR3IF = 0;

	// Start TMR3
	TMR3_StartTimer();
}

void TMR3_StartTimer(void) {
	// Start the Timer by writing to TMRxON bit
	T3CONbits.TMR3ON = 1;
}

void TMR3_StopTimer(void) {
	// Stop the Timer by writing to TMRxON bit
	T3CONbits.TMR3ON = 0;
}

uint16_t TMR3_ReadTimer(void) {
	uint16_t readVal;
	uint8_t readValHigh;
	uint8_t readValLow;

	readValLow = TMR3L;
	readValHigh = TMR3H;

	readVal = ((uint16_t)readValHigh << 8) | readValLow;

	return readVal;
}

void TMR3_WriteTimer(uint16_t timerVal) {
	if (T3CONbits.nT3SYNC == 1) {
		// Stop the Timer by writing to TMRxON bit
		T3CONbits.TMR3ON = 0;

		// Write to the Timer3 register
		TMR3H = (timerVal >> 8);
		TMR3L = (uint8_t)timerVal;

		// Start the Timer after writing to the register
		T3CONbits.TMR3ON = 1;
	}
	else {
		// Write to the Timer3 register
		TMR3H = (timerVal >> 8);
		TMR3L = (uint8_t)timerVal;
	}
}

void TMR3_Reload(void) {
	// Write to the Timer3 register
	TMR3H = (timer3ReloadVal >> 8);
	TMR3L = (uint8_t)timer3ReloadVal;
}

void TMR3_StartSinglePulseAcquisition(void) {
	T3GCONbits.T3GGO = 1;
}

uint8_t TMR3_CheckGateValueStatus(void) {
	return T3GCONbits.T3GVAL;
}

bool TMR3_HasOverflowOccured(void) {
	// check if  overflow has occurred by checking the TMRIF bit
	return (PIR2bits.TMR3IF);
}

/**
 End of File
 */
