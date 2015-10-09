/* 
 * File:   StepperFuncs.h
 * Author: Lance
 *
 * Created on June 15, 2015, 8:15 PM
 */

#ifndef STEPPERFUNCS_H
#define	STEPPERFUNCS_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define OFF_STATE 8
    

#define S1P1_TRIS              TRISA0
#define S1P1_LAT               LATA0
#define S1P1_PORT              PORTAbits.RA0
#define S1P1_ANS               ANSA0
    
#define S1I11_TRIS             TRISA1
#define S1I11_LAT              LATA1
#define S1I11_PORT             PORTAbits.RA1
#define S1I11_ANS              ANSA1
    
#define S1I01_TRIS             TRISA2
#define S1I01_LAT              LATA2
#define S1I01_PORT             PORTAbits.RA2
#define S1I01_ANS              ANSA2
    
#define S1P2_TRIS              TRISA3
#define S1P2_LAT               LATA3
#define S1P2_PORT              PORTAbits.RA3
#define S1P2_ANS               ANSA3
    
#define S1I12_TRIS             TRISA5
#define S1I12_LAT              LATA5
#define S1I12_PORT             PORTAbits.RA5
#define S1I12_ANS              ANSA5
    
#define S2I01_TRIS             TRISA6
#define S2I01_LAT              LATA6
#define S2I01_PORT             PORTAbits.RA6
    
#define S1I02_TRIS             TRISA7
#define S1I02_LAT              LATA7
#define S1I02_PORT             PORTAbits.RA7
    
#define Limit2_TRIS            TRISB0
#define Limit2_LAT             LATB0
#define Limit2_PORT            PORTBbits.RB0
#define Limit2_WPU             WPUB0
#define Limit2_ANS             ANSB0

#define Limit1_TRIS            TRISB1
#define Limit1_LAT             LATB1
#define Limit1_PORT            PORTBbits.RB1
#define Limit1_WPU             WPUB1
#define Limit1_ANS             ANSB1
    
#define Button1_TRIS           TRISB2
#define Button1_LAT            LATB2
#define Button1_PORT           PORTBbits.RB2
#define Button1_WPU            WPUB2
#define Button1_ANS            ANSB2
    
#define Button2_TRIS           TRISB3
#define Button2_LAT            LATB3
#define Button2_PORT           PORTBbits.RB3
#define Button2_WPU            WPUB3
#define Button2_ANS            ANSB3
        
#define LED2_TRIS              TRISB4
#define LED2_LAT               LATB4
#define LED2_PORT              PORTBbits.RB4
#define LED2_WPU               WPUB4
#define LED2_ANS               ANSB4
    
#define LED1_TRIS              TRISB5
#define LED1_LAT               LATB5
#define LED1_PORT              PORTBbits.RB5
#define LED1_WPU               WPUB5
#define LED1_ANS               ANSB5    
    
#define S2I11_TRIS             TRISC0
#define S2I11_LAT              LATC0
#define S2I11_PORT             PORTCbits.RC0
    
#define S2P1_TRIS              TRISC1
#define S2P1_LAT               LATC1
#define S2P1_PORT              PORTCbits.RC1
    
#define S2I12_TRIS             TRISC2
#define S2I12_LAT              LATC2
#define S2I12_PORT             PORTCbits.RC2
#define S2I12_ANS              ANSC2
    
#define S2P2_TRIS              TRISC3
#define S2P2_LAT               LATC3
#define S2P2_PORT              PORTCbits.RC3
#define S2P2_ANS               ANSC3
    
#define S2I02_TRIS             TRISC4
#define S2I02_LAT              LATC4
#define S2I02_PORT             PORTCbits.RC4
#define S2I02_ANS              ANSC4
    
#define masterLED_TRIS         TRISC5
#define masterLED_LAT          LATC5
#define masterLED_PORT         PORTCbits.RC5
#define masterLED_ANS          ANSC5
    
#define TX1_TRIS               TRISC6
#define TX1_LAT                LATC6
#define TX1_PORT               PORTCbits.RC6
#define TX1_ANS                ANSC6
    
#define RX1_TRIS               TRISC7
#define RX1_LAT                LATC7
#define RX1_PORT               PORTCbits.RC7
#define RX1_ANS                ANSC7
    
       

volatile uint8_t S1Move;
volatile uint8_t S2Move;
volatile uint8_t S1PWMState;
volatile uint8_t S2PWMState;
volatile uint8_t S1StepState;
volatile uint8_t S2StepState;
    
volatile uint16_t S1TotalSteps;
volatile uint16_t S2TotalSteps;

const uint16_t TReload[128] = { 
    0xFFFF,  //0
    0xFFFF,  //1
    0x3CB0,  //2
    0x7DCB,  //3
    0x9E58,  //4
    0xB1E0,  //5
    0xBEE6,  //6
    0xC833,  //7
    0xCF2C,  //8
    0xD499,  //9
    0xD8F0,  //10
    0xDC7E,  //11
    0xDF73,  //12
    0xE1F4,  //13
    0xE41A,  //14
    0xE5F6,  //15
    0xE796,  //16
    0xE906,  //17
    0xEA4D,  //18
    0xEB71,  //19
    0xEC78,  //20
    0xED67,  //21
    0xEE3F,  //22
    0xEF05,  //23
    0xEFBA,  //24
    0xF060,  //25
    0xF0FA,  //26
    0xF189,  //27
    0xF20D,  //28
    0xF288,  //29
    0xF2FB,  //30
    0xF367,  //31
    0xF3CB,  //32
    0xF42A,  //33
    0xF483,  //34
    0xF4D7,  //35
    0xF527,  //36
    0xF572,  //37
    0xF5B9,  //38
    0xF5FC,  //39
    0xF63C,  //40
    0xF679,  //41
    0xF6B4,  //42
    0xF6EB,  //43
    0xF720,  //44
    0xF752,  //45
    0xF783,  //46
    0xF7B1,  //47
    0xF7DD,  //48
    0xF808,  //49
    0xF830,  //50
    0xF858,  //51
    0xF87D,  //52
    0xF8A2,  //53
    0xF8C5,  //54
    0xF8E6,  //55
    0xF907,  //56
    0xF926,  //57
    0xF944,  //58
    0xF962,  //59
    0xF97E,  //60
    0xF999,  //61
    0xF9B4,  //62
    0xF9CD,  //63
    0xF9E6,  //64
    0xF9FE,  //65
    0xFA15,  //66
    0xFA2C,  //67
    0xFA42,  //68
    0xFA57,  //69
    0xFA6C,  //70
    0xFA80,  //71
    0xFA94,  //72
    0xFAA7,  //73
    0xFAB9,  //74
    0xFACB,  //75
    0xFADD,  //76
    0xFAEE,  //77
    0xFAFE,  //78
    0xFB0F,  //79
    0xFB1E,  //80
    0xFB2E,  //81
    0xFB3D,  //82
    0xFB4C,  //83
    0xFB5A,  //84
    0xFB68,  //85
    0xFB76,  //86
    0xFB83,  //87
    0xFB90,  //88
    0xFB9D,  //89
    0xFBA9,  //90
    0xFBB6,  //91
    0xFBC2,  //92
    0xFBCD,  //93
    0xFBD9,  //94
    0xFBE4,  //95
    0xFBEF,  //96
    0xFBFA,  //97
    0xFC04,  //98
    0xFC0E,  //99
    0xFC18,  //100
    0xFC22,  //101
    0xFC2C,  //102
    0xFC36,  //103
    0xFC3F,  //104
    0xFC48,  //105
    0xFC51,  //106
    0xFC5A,  //107
    0xFC63,  //108
    0xFC6B,  //109
    0xFC73,  //110
    0xFC7C,  //111
    0xFC84,  //112
    0xFC8C,  //113
    0xFC93,  //114
    0xFC9B,  //115
    0xFCA2,  //116
    0xFCAA,  //117
    0xFCB1,  //118
    0xFCB8,  //119
    0xFCBF,  //120
    0xFCC6,  //121
    0xFCCD,  //122
    0xFCD3,  //123
    0xFCDA,  //124
    0xFCE0,  //125
    0xFCE7,  //126
    0xFCED,  //127
};

    
void stepperInit();
void processSteppers();

void s1Step(uint8_t StepID);
void s2Step(uint8_t StepID);

#ifdef	__cplusplus
}
#endif

#endif	/* STEPPERFUNCS_H */

