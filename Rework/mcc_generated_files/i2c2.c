/**
  MSSP2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c2.c

  @Summary
    This is the generated header file for the MSSP2 driver using 
    MPLAB® Code Configurator

  @Description
    This header file provides APIs for driver for MSSP2.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC18F24K22
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB 	          :  MPLAB X v2.35 or v3.00
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

#include "mcc.h"

#define I2C2_SLAVE_ADDRESS 8
#define I2C2_SLAVE_MASK    127

/**
 Section: Global Variables
 */

volatile uint8_t I2C2_slaveWriteData = 0x55;

/**
 Section: Local Functions
 */
void I2C2_StatusCallback(I2C2_SLAVE_DRIVER_STATUS i2c_bus_state);

/**
  Prototype:        void I2C2_Initialize(void)
  Input:            none
  Output:           none
  Description:      I2C2_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            I2C2_Initialize();

 */
void I2C2_Initialize(void) {
    // initialize the hardware
    // BF RCinprocess_TXcomplete; UA dontupdate; SMP Sample At Middle; P stopbit_notdetected; S startbit_notdetected; R_nW write_noTX; CKE Idle to Active; D_nA lastbyte_address; 
    SSP2STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; SSPOV no_overflow; CKP Idle:Low, Active:High; SSPM 7 Bit; 
    SSP2CON1 = 0x26;
    // ACKSTAT received; RCEN disabled; RSEN disabled; ACKEN disabled; SEN disabled; ACKDT acknowledge; GCEN disabled; PEN disabled; 
    SSP2CON2 = 0x00;
    // BOEN disabled; AHEN disabled; SBCDE disabled; SDAHT 100ns; DHEN disabled; ACKTIM ackseq; PCIE disabled; SCIE disabled; 
    SSP2CON3 = 0x00;
    // MSK0 127; 
    SSP2MSK = (I2C2_SLAVE_MASK << 1); // adjust UI mask for R/nW bit            
    // SSPADD 8; 
    SSP2ADD = (I2C2_SLAVE_ADDRESS << 1); // adjust UI address for R/nW bit

    // clear the slave interrupt flag
    PIR3bits.SSP2IF = 0;
    // enable the master interrupt
    PIE3bits.SSP2IE = 1;

}

void I2C2_ISR(void) {
    uint8_t i2c_data = 0x55;


    // NOTE: The slave driver will always acknowledge
    //       any address match.

    PIR3bits.SSP2IF = 0; // clear the slave interrupt flag
    i2c_data = SSP2BUF; // read SSPBUF to clear BF
    if (1 == SSP2STATbits.R_nW) {
        if ((1 == SSP2STATbits.D_nA) && (1 == SSP2CON2bits.ACKSTAT)) {
            // callback routine can perform any post-read processing
            I2C2_StatusCallback(I2C2_SLAVE_READ_COMPLETED);
        } else {
            // callback routine should write data into SSPBUF
            I2C2_StatusCallback(I2C2_SLAVE_READ_REQUEST);
        }
    } else if (0 == SSP2STATbits.D_nA) {
        // this is an I2C address

        // callback routine should prepare to receive data from the master
        I2C2_StatusCallback(I2C2_SLAVE_WRITE_REQUEST);
    } else {
        I2C2_slaveWriteData = i2c_data;

        // callback routine should process I2C2_slaveWriteData from the master
        I2C2_StatusCallback(I2C2_SLAVE_WRITE_COMPLETED);
    }

    SSP2CON1bits.CKP = 1; // release SCL

} // end I2C2_ISR()

/**

    Example implementation of the callback

    This slave driver emulates an EEPROM Device.
    Sequential reads from the EEPROM will return data at the next
    EEPROM address.

    Random access reads can be performed by writing a single byte
    EEPROM address, followed by 1 or more reads.

    Random access writes can be performed by writing a single byte
    EEPROM address, followed by 1 or more writes.

    Every read or write will increment the internal EEPROM address.

    When the end of the EEPROM is reached, the EEPROM address will
    continue from the start of the EEPROM.
 */

void I2C2_StatusCallback(I2C2_SLAVE_DRIVER_STATUS i2c_bus_state) {

    switch (i2c_bus_state) {
        case I2C2_SLAVE_WRITE_REQUEST:
            // the master will be sending the eeprom address next

            break;


        case I2C2_SLAVE_WRITE_COMPLETED:
           // read from the i2c bus
           // = I2C2_slaveWriteData

            break;

        case I2C2_SLAVE_READ_REQUEST:
            //write to the read buffer
            //SSP2BUF = 
            break;

        case I2C2_SLAVE_READ_COMPLETED:
        default:;

    } // end switch(i2c_bus_state)

}

