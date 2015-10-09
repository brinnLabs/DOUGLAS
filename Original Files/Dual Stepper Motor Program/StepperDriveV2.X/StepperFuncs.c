#include "main.h"
#include "StepperFuncs.h"

//volatile uint8_t S1Move;
//volatile uint8_t S2Move;
//volatile uint8_t S1PWMState;
//volatile uint8_t S2PWMState;
//volatile uint8_t S1StepState;
//volatile uint8_t S2StepState;

//volatile uint16_t S1TotalSteps;
//volatile uint16_t S2TotalSteps;

extern volatile LSTATES L1State;
extern volatile LSTATES L2State;

void stepperInit()
{
    S1PWMState = 1;
    S2PWMState = 1;
    
    S1StepState = 0;
    S2StepState = 0;
    
    S1Move = 0;
    S2Move = 0;
}

void processSteppers()
{
    // Check PWM State flag
    if (PIR5bits.TMR6IF)
    {
        S1PWMState++;
        S1PWMState&=0x03;
        S2PWMState++;
        S2PWMState&=0x03;
        PIR5bits.TMR6IF = 0;
    }
    
    // Check TMR3 flag
    if (PIR2bits.TMR3IF)
    {        
        PIR2bits.TMR3IF = 0;
        TMR3 = timer3ReloadVal;
        S1PWMState = 0x01;
        if ((S1Move&0x7F)>0)
        {
            if (S1Move&0x80)
            {
                if (L1State != LIMIT_POS)// && S1TotalSteps < MAXSTEPS)
                {
                    S1StepState++;
                    S1TotalSteps++;
                }
            }
            else
            {
                if (L1State != LIMIT_NEG)
                {
                    S1StepState--;
                    if (S1TotalSteps > 0)
                    {
                        S1TotalSteps--;
                    }
                }
            }
            S1StepState&=0x07;
            S1Move--;
        }
        if (0==(S1Move&0x7F))
        {
            T3CONbits.TMR3ON = 0;
        }
    }
    
    // Check TMR5 flag
    if (PIR5bits.TMR5IF)
    {
        PIR5bits.TMR5IF = 0;
        TMR5 = timer5ReloadVal;
        S2PWMState = 0x01;
        if ((S2Move&0x7F)>0)
        {
            if (S2Move&0x80)
            {
                if (L2State != LIMIT_POS)// && S2TotalSteps < MAXSTEPS)
                {
                    S2StepState++;
                    S2TotalSteps++;
                }
            }
            else
            {
                if (L2State != LIMIT_NEG)
                {
                    S2StepState--;
                    if (S2TotalSteps > 0)
                    {
                        S2TotalSteps--;
                    }
                }
            }
            S2StepState&=0x07;
            S2Move--;
        }
        if (0 == (S2Move&0x7F))
        {
            T5CONbits.TMR5ON = 0;
        }
    }
    
    if (S1PWMState)
    {
        s1Step(S1StepState);
    }
    else
    {
        s1Step(OFF_STATE);
    }
    
    if (S2PWMState)
    {
        s2Step(S2StepState);
    }
    else
    {
        s2Step(OFF_STATE);
    }    
}


void s1Step(uint8_t StepID)
{
    switch (StepID)
    {
        case 0:
            S1I01_LAT   = 0;
            S1I11_LAT   = 0;
            S1P1_LAT    = 1;
            S1I02_LAT   = 1;
            S1I12_LAT   = 1;
            S1P2_LAT    = 1;
            break;
        case 1:
            S1I01_LAT   = 1;
            S1I11_LAT   = 0;
            S1P1_LAT    = 1;
            S1I02_LAT   = 1;
            S1I12_LAT   = 0;
            S1P2_LAT    = 1;
            break;
        case 2:
            S1I01_LAT   = 1;
            S1I11_LAT   = 1;
            S1P1_LAT    = 0;
            S1I02_LAT   = 0;
            S1I12_LAT   = 0;
            S1P2_LAT    = 1;
            break;
        case 3:
            S1I01_LAT   = 1;
            S1I11_LAT   = 0;
            S1P1_LAT    = 0;
            S1I02_LAT   = 1;
            S1I12_LAT   = 0;
            S1P2_LAT    = 1;
            break;
        case 4:
            S1I01_LAT   = 0;
            S1I11_LAT   = 0;
            S1P1_LAT    = 0;
            S1I02_LAT   = 1;
            S1I12_LAT   = 1;
            S1P2_LAT    = 0;
            break;
        case 5:
            S1I01_LAT   = 1;
            S1I11_LAT   = 0;
            S1P1_LAT    = 0;
            S1I02_LAT   = 1;
            S1I12_LAT   = 0;
            S1P2_LAT    = 0;
            break;
        case 6:
            S1I01_LAT   = 1;
            S1I11_LAT   = 1;
            S1P1_LAT    = 1;
            S1I02_LAT   = 0;
            S1I12_LAT   = 0;
            S1P2_LAT    = 0;
            break;
        case 7:
            S1I01_LAT   = 1;
            S1I11_LAT   = 0;
            S1P1_LAT    = 1;
            S1I02_LAT   = 1;
            S1I12_LAT   = 0;
            S1P2_LAT    = 0;
            break;
        default: // Turn off the stepper
            S1I01_LAT   = 1;
            S1I11_LAT   = 1;
            S1P1_LAT    = 0;
            S1I02_LAT   = 1;
            S1I12_LAT   = 1;
            S1P2_LAT    = 0;
            break;
    }
}

void s2Step(uint8_t StepID)
{
    switch (StepID)
    {
        case 0:
            S2I01_LAT   = 0;
            S2I11_LAT   = 0;
            S2P1_LAT    = 1;
            S2I02_LAT   = 1;
            S2I12_LAT   = 1;
            S2P2_LAT    = 1;
            break;
        case 1:
            S2I01_LAT   = 1;
            S2I11_LAT   = 0;
            S2P1_LAT    = 1;
            S2I02_LAT   = 1;
            S2I12_LAT   = 0;
            S2P2_LAT    = 1;
            break;
        case 2:
            S2I01_LAT   = 1;
            S2I11_LAT   = 1;
            S2P1_LAT    = 0;
            S2I02_LAT   = 0;
            S2I12_LAT   = 0;
            S2P2_LAT    = 1;
            break;
        case 3:
            S2I01_LAT   = 1;
            S2I11_LAT   = 0;
            S2P1_LAT    = 0;
            S2I02_LAT   = 1;
            S2I12_LAT   = 0;
            S2P2_LAT    = 1;
            break;
        case 4:
            S2I01_LAT   = 0;
            S2I11_LAT   = 0;
            S2P1_LAT    = 0;
            S2I02_LAT   = 1;
            S2I12_LAT   = 1;
            S2P2_LAT    = 0;
            break;
        case 5:
            S2I01_LAT   = 1;
            S2I11_LAT   = 0;
            S2P1_LAT    = 0;
            S2I02_LAT   = 1;
            S2I12_LAT   = 0;
            S2P2_LAT    = 0;
            break;
        case 6:
            S2I01_LAT   = 1;
            S2I11_LAT   = 1;
            S2P1_LAT    = 1;
            S2I02_LAT   = 0;
            S2I12_LAT   = 0;
            S2P2_LAT    = 0;
            break;
        case 7:
            S2I01_LAT   = 1;
            S2I11_LAT   = 0;
            S2P1_LAT    = 1;
            S2I02_LAT   = 1;
            S2I12_LAT   = 0;
            S2P2_LAT    = 0;
            break;
        default: // Turn off the stepper
            S2I01_LAT   = 1;
            S2I11_LAT   = 1;
            S2P1_LAT    = 0;
            S2I02_LAT   = 1;
            S2I12_LAT   = 1;
            S2P2_LAT    = 0;
            break;
    }
}
