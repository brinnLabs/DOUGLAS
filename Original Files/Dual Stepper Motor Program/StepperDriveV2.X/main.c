/*
 * Simple Stepper Controller - optimized 
 * 
 * We need several timers to do the following:
 * 
 *  /---------- Interrupt
 *  |
 *      100ms   Global Step Timer - TMR0
 *              Every Step we update our stepper times
 * 
 *      1ms     Packet Reset Timer - TMR2
 *              Every RX byte resets this timer, if it
 *              expires then we reset the received byte counter
 * 
 *  I   50us    Byte TX timer - TMR4
 *              We only transmit one byte every ByteTXTimer delay
 *              This is to allow further controllers to handle data
 * 
 *      s1Time  Stepper One delay Time - TMR3
 *              Every time s1Time expires we step the first stepper
 * 
 *      s2Time  Stepper Two delay Time - TMR5
 *              Every time s2Time expires we step the second stepper
 * 
 *      sPWM    Stepper PWM Timer - TMR6
 *              Drives the stepper PWM state machine.  Free running.
 * 
 * 
 * Other Interrupts
 * 
 *  EUSART RX - Incoming bytes should be handled ASAP
 * 
 *  
 * 
 */

#include "main.h"
#include "StepperFuncs.h"

extern uint8_t rnd();
uint8_t random   @ 0x20;

extern volatile uint8_t S1Move;
extern volatile uint8_t S2Move;

extern volatile uint16_t S1TotalSteps;
extern volatile uint16_t S2TotalSteps;


#define MAX_BUFFER 16
#define BUFFER_MASK 0x0F

volatile uint8_t totalNodes;
volatile uint8_t cByte;

uint8_t cmdCount;

typedef struct
{
    uint8_t buff[MAX_BUFFER];
    uint8_t head;
    uint8_t size;
} BUFFER;

volatile BUFFER sBuff[2];
volatile BUFFER txBuff;

volatile uint8_t RXCmd; // 0 = No Command, 1 = In Command, 2 = Cmd Complete
volatile uint8_t CMDBuff[3]; // Command Buffer

void init(void)
{
    // Init Oscillator
    // Set to 32Mhz
    OSCCON  = 0x60;
    OSCCON2 = 0x04;
    OSCTUNE = 0x40;
    
    // Set up ports
    LATA = 0x00;
    TRISA = 0x10;
    ANSELA = 0x00;

    LATB = 0x00;
    TRISB = 0xC3;
    ANSELB = 0x00;
    WPUB = 0x03;

    LATC = 0x00;
    TRISC = 0xC0;
    ANSELC = 0x00;

    INTCON2bits.nRBPU = 0x00;
    
    
    // Init Timers
    // TMR0 - 100ms interval Global Step Timer
    T0CON = 0x13;
    TMR0H = 0x3C;
    TMR0L = 0xB0;
    
    timer0ReloadVal = TMR0;//15536;
    
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 0;  //  No TMR0 Interrupt
    
    // TMR2
    T2CON   = 0x0A;
    PR2     = 0xF9;
    TMR2    = 0x00;
    
    PIR1bits.TMR2IF = 0;
    PIE1bits.TMR2IE = 0; // No TMR2 Interrupt
    
    // TMR3
    T3CON   = 0x30;
    T3GCON  = 0x00;
    TMR3H   = 0xD8;
    TMR3L   = 0xF0;
    
    timer3ReloadVal = TMR3;
    
    PIR2bits.TMR3IF = 0;
    PIE2bits.TMR3IE = 0; // No TMR3 interrupt    
    
    // TMR4
    T4CON   = 0x01;
    PR4     = 0x63;
    TMR4    = 0x00;
    
    PIR5bits.TMR4IF = 0;
    PIE5bits.TMR4IE = 1; // TMR4 interrupt
        
    // TMR5
    T5CON   = 0x30;
    T5GCON  = 0x00;
    TMR5H   = 0xD8;
    TMR5L   = 0xF0;
    
    timer5ReloadVal = TMR5;
    
    PIR5bits.TMR5IF = 0;
    PIE5bits.TMR5IE = 0; // No TMR5 interrupt
    
    // TMR6
    T6CON   = 0x0A;
    PR6     = 0xFF;
    TMR6    = 0x00;
    
    PIR5bits.TMR6IF = 0;
    PIE5bits.TMR6IE = 0; // No TMR6 interrupt
    
    
    // Init UART
    PIE1bits.RC1IE = 0;
    PIE1bits.TX1IE = 0;
    
    BAUD1CON    = 0x48;
    RC1STA      = 0x90;
    TX1STA      = 0x26;
    SPBRG1      = 0x07;//0x27;//0x0F;
    SPBRGH1     = 0x00;  // 200000
    
    // Setup Interrupts
    PIE1bits.RC1IE = 1;
    PIE1bits.TX1IE = 0;
    PIR1bits.TX1IF = 0;
    
    sBuff[0].head = 0;
    sBuff[0].size = 0;
    sBuff[1].head = 0;
    sBuff[1].size = 0;
    txBuff.head = 0;
    txBuff.size = 0;
    
    totalNodes = 120;
    cByte = 0;
        
    S1TotalSteps = 0;
    S2TotalSteps = 0;
    
    
    // Script Execution
    ScriptLoc = 0;
    cmdCount = CMDREPEAT;
    
}

void interrupt Interrupt_Handler(void)
{
    uint8_t tByte;
    //LATB2 = 1;
    // We should only get two interrupts that matter
    // TX Timer
    // EUSART RX
    if (PIR1bits.RC1IF)
    { 
        TMR2 = 0;
        if (!T2CONbits.TMR2ON)
        {
            T2CONbits.TMR2ON = 1;
            //LATB3 = 1;
        }
        if (1 == RC1STAbits.OERR) 
        {
            // EUSART1 error - restart

            RC1STAbits.CREN = 0;
            RC1STAbits.CREN = 1;
        }    
        
        tByte = RCREG1;
//        if (RXCmd==1 || (cByte == 0 && tByte == 0xff))
//        {
//            RXCmd = 1;
//            CMDBuff[cByte] = RCREG1;
//            TXREG1 = RCREG1;
//            PIE1bits.TX1IE = 1;
//            if (cByte == 2)
//            {
//                RXCmd = 2;
//                cByte = 0;
//            }
//        }
//        else
        {
            if (cByte < 2)
            {
                //LATB3 = 1;
                if (sBuff[cByte].size < MAX_BUFFER)
                {
                    sBuff[cByte].buff[(sBuff[cByte].head+sBuff[cByte].size)&BUFFER_MASK] = tByte;
                    sBuff[cByte].size++;
                }
            }
            else if (cByte == totalNodes-1)
            { // We just received the last node, now send response
                if (!T4CONbits.TMR4ON)
                {
                    LATB3 = 1;
                    TMR4 = 0;
                    PIR5bits.TMR4IF = 1;
                    T4CONbits.TMR4ON = 1;
                    LATB3 = 0;
                    //LATB3 = T4CONbits.TMR4ON;
                }
                txBuff.buff[(txBuff.head+txBuff.size)&BUFFER_MASK] = tByte;
                txBuff.size++;
                txBuff.buff[(txBuff.head+txBuff.size)&BUFFER_MASK] = ((sBuff[0].size<<4)&0xF0) | (sBuff[1].size&0x0F);
                txBuff.size++;
                txBuff.buff[(txBuff.head+txBuff.size)&BUFFER_MASK] = (L2State<<4)|L1State;
                txBuff.size++;
            }
            else
            { // Pass through!
                //LATB3 = 0;
                if (!T4CONbits.TMR4ON)
                {
                    LATB3 = 1;
                    TMR4 = 0;
                    PIR5bits.TMR4IF = 1;
                    T4CONbits.TMR4ON = 1;
                    LATB3 = 0;
                    //LATB3 = T4CONbits.TMR4ON;
                }
                txBuff.buff[(txBuff.head+txBuff.size)&BUFFER_MASK] = tByte;
                txBuff.size++;
            }
        }
        cByte++;
    }
    
    if (PIR5bits.TMR4IF)
    { // Send a byte!
        //TXREG1 = SendByte;
        LATB2 = 1;
        if (txBuff.size)
        {
            TXREG1 = txBuff.buff[txBuff.head];
            txBuff.head++;
            txBuff.head&=BUFFER_MASK;
            txBuff.size--;
        }
        if (!T2CONbits.TMR2ON && !txBuff.size)
        {
            T4CONbits.TMR4ON = 0;
            //LATB3 = T4CONbits.TMR4ON;
        }
        PIR5bits.TMR4IF = 0;
        LATB2 = 0;
    }
}

void checkLimits(void)
{
    if (Limit1_PORT)
    {
        LED1_LAT = 0;
        L1Debounce = 0;
        L1State = NO_LIMIT;
    }
    else
    {
        if ((L1Debounce > DEBOUNCE_COUNT) && (L1State == NO_LIMIT))
        {
            LED1_LAT = 1;
            if (S1Move&0x80)
            {
                L1State = LIMIT_POS;
            }
            else
            {
                L1State = LIMIT_NEG;
            }
            S1TotalSteps = 0;
        }
        else
        {
            L1Debounce++;
        }
    }
   
    if (Limit2_PORT)
    {
        LED2_LAT = 0;
        L2Debounce = 0;
        L2State = NO_LIMIT;
    }
    else
    {
        if ((L2Debounce > DEBOUNCE_COUNT) && (L2State == NO_LIMIT))
        {
            LED2_LAT = 1;
            if (S2Move&0x80)
            {
                L2State = LIMIT_POS;
            }
            else
            {
                L2State = LIMIT_NEG;
            }
            S2TotalSteps = 0;
        }
        else
        {
            L2Debounce++;
        }
    }
}

void main(void)
{
    uint8_t temp;
    init();
    stepperInit();
    random = 42;
    L1Debounce = 0;
    L2Debounce = 0;
    L1State = NO_LIMIT;
    L2State = NO_LIMIT;
        
    // TODO: Start Timers
    T0CONbits.TMR0ON = 1; // Start 100ms timer
    //T2CONbits.TMR2ON = 1; // Start 1ms timer
    //T3CONbits.TMR3ON = 1; // Stepper Timer stays off until a command
    //T5CONbits.TMR5ON = 1; // Stepper Timer stays off until a command
    //T4CONbits.TMR4ON = 1; // Start 50us timer - 
    T6CONbits.TMR6ON = 1; // Start Stepper PWM Timer
    
    // TODO: Implement Communications
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    
    
    /// TODO remove next 4 lines - diagnostics!
//    S1Move = 20;
//    S2Move = 20;
//    T3CONbits.TMR3ON = 1; // Stepper Timer stays off until a command
//    T5CONbits.TMR5ON = 1; // Stepper Timer stays off until a command
    
    while (1)
    {
//        LATB3 = T4CONbits.TMR4ON;
        // Check TMR0
        
        /*
        if (RXCmd&0x02)
        {  // We have a command
            if ((CMDBuff[1]&0xF0) == 0)
            { // ARRAY SIZE
                totalNodes = CMDBuff[2];
            }
            if (CMDBuff[1] == 0xFF)
            {
                if (CMDBuff[2] == 0xFF)
                { // Reset the TMR0 to roughly sync it
                    TMR0 = timer0ReloadVal;
                }
                if (CMDBuff[2] == 0x00)
                {
                    sBuff[0].size = 0;
                    sBuff[1].size = 0;
                }
                
            }
            
            CMDBuff[0] = 0;
            RXCmd = 0; // Command Handled, ready for next            
        }*/
        
        if (INTCONbits.TMR0IF)
        { // Master 100ms timer
            masterLED_PORT = ~masterLED_PORT;
            TMR0 = timer0ReloadVal;
            INTCONbits.TMR0IF = 0;
            
            // if there is data in the buffer, then we should move :)
            //if (sBuff[1].size > 0 && sBuff[0].size > 0)    
            // We have a script - execute every cycle
            {
                INTCONbits.GIE = 0;
                S1Move = ScriptData[ScriptLoc];//sBuff[0].buff[sBuff[0].head];
//                sBuff[0].head++;
//                sBuff[0].head &= BUFFER_MASK;
//                sBuff[0].size--;
                if (S1Move&0x40)
                {
                    rnd();
                    temp = random&0x3f;
                    temp |= S1Move&0x80;
                    S1Move = temp;
                }
                
                if (S1Move&0x7F)
                {
                    PIR2bits.TMR3IF = 1;
                    S1Move--;
                    if (S1Move&0x7F)
                    {
                        timer3ReloadVal = TReload[S1Move&0x7F];
                        T3CONbits.TMR3ON = 1;
                    }
                }
                else
                {
                    T3CONbits.TMR3ON = 0;
                    S1Move = 0;
                }
                INTCONbits.GIE = 1;
            }
            
            //if (sBuff[1].size > 0)    
            // We have a script - execute every cycle
            {
                INTCONbits.GIE = 0;
                S2Move = ScriptData[ScriptLoc+1];//sBuff[1].buff[sBuff[1].head];
//                sBuff[1].head++;
//                sBuff[1].head &= BUFFER_MASK;
//                sBuff[1].size--;
                if (S2Move&0x40)
                {
                    rnd();
                    temp = random&0x3f;
                    temp |= S2Move&0x80;
                    S2Move = temp;
                }
                if (S2Move&0x7F)
                {
                    PIR5bits.TMR5IF = 1;
                    S2Move--;
                    if (S2Move&0x7F)
                    {
                        timer5ReloadVal = TReload[S2Move&0x7F];
                        T5CONbits.TMR5ON = 1;
                    }
                }
                else
                {
                    T5CONbits.TMR5ON = 0;
                    S2Move = 0;
                }
                INTCONbits.GIE = 1;
            }
            if (cmdCount == 0)
            {
                ScriptLoc+=2;
                ScriptLoc%=ScriptSize;
                cmdCount = CMDREPEAT;
            }
            else
            {
                cmdCount--;
            }
        }
        
        // Check TMR2
        if (PIR1bits.TMR2IF)
        { // Packet reset timer (1ms)
            cByte = 0;
            //LATB3 = 0;
            PIR1bits.TMR2IF = 0;
            T2CONbits.TMR2ON = 0;
        }             
        
        // Checks TMR3, TMR5, TMR6
        processSteppers();
        checkLimits();
    }
}
