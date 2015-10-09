#include "stepper.h"

void stepperInit(void) {
	step1Count = 0;
	step2Count = 0;
}

void stepper1Step(bool dir)
{
	switch (step1Count % 8)
	{
	case 0:
		LATA2 = 0;
		LATA1 = 0;
		LATA0 = 1;
		LATA7 = 1;
		LATA5 = 1;
		LATA3 = 1;
		break;
	case 1:
		LATA2 = 1;
		LATA1 = 0;
		LATA0 = 1;
		LATA7 = 1;
		LATA5 = 0;
		LATA3 = 1;
		break;
	case 2:
		LATA2 = 1;
		LATA1 = 1;
		LATA0 = 0;
		LATA7 = 0;
		LATA5 = 0;
		LATA3 = 1;
		break;
	case 3:
		LATA2 = 1;
		LATA1 = 0;
		LATA0 = 0;
		LATA7 = 1;
		LATA5 = 0;
		LATA3 = 1;
		break;
	case 4:
		LATA2 = 0;
		LATA1 = 0;
		LATA0 = 0;
		LATA7 = 1;
		LATA5 = 1;
		LATA3 = 0;
		break;
	case 5:
		LATA2 = 1;
		LATA1 = 0;
		LATA0 = 0;
		LATA7 = 1;
		LATA5 = 0;
		LATA3 = 0;
		break;
	case 6:
		LATA2 = 1;
		LATA1 = 1;
		LATA0 = 1;
		LATA7 = 0;
		LATA5 = 0;
		LATA3 = 0;
		break;
	case 7:
		LATA2 = 1;
		LATA1 = 0;
		LATA0 = 1;
		LATA7 = 1;
		LATA5 = 0;
		LATA3 = 0;
		break;
	default: // Turn off the stepper
		LATA2 = 1;
		LATA1 = 1;
		LATA0 = 0;
		LATA7 = 1;
		LATA5 = 1;
		LATA3 = 0;
		break;
	}

	if (dir)
		step1Count++;
	else
		step1Count--;
}

void stepper2Step(bool dir)
{
	switch (step2Count % 8)
	{
	case 0:
		LATA6 = 0;
		LATC0 = 0;
		LATC1 = 1;
		LATC4 = 1;
		LATC2 = 1;
		LATC3 = 1;
		break;
	case 1:
		LATA6 = 1;
		LATC0 = 0;
		LATC1 = 1;
		LATC4 = 1;
		LATC2 = 0;
		LATC3 = 1;
		break;
	case 2:
		LATA6 = 1;
		LATC0 = 1;
		LATC1 = 0;
		LATC4 = 0;
		LATC2 = 0;
		LATC3 = 1;
		break;
	case 3:
		LATA6 = 1;
		LATC0 = 0;
		LATC1 = 0;
		LATC4 = 1;
		LATC2 = 0;
		LATC3 = 1;
		break;
	case 4:
		LATA6 = 0;
		LATC0 = 0;
		LATC1 = 0;
		LATC4 = 1;
		LATC2 = 1;
		LATC3 = 0;
		break;
	case 5:
		LATA6 = 1;
		LATC0 = 0;
		LATC1 = 0;
		LATC4 = 1;
		LATC2 = 0;
		LATC3 = 0;
		break;
	case 6:
		LATA6 = 1;
		LATC0 = 1;
		LATC1 = 1;
		LATC4 = 0;
		LATC2 = 0;
		LATC3 = 0;
		break;
	case 7:
		LATA6 = 1;
		LATC0 = 0;
		LATC1 = 1;
		LATC4 = 1;
		LATC2 = 0;
		LATC3 = 0;
		break;
	default: // Turn off the stepper
		LATA6 = 1;
		LATC0 = 1;
		LATC1 = 0;
		LATC4 = 1;
		LATC2 = 1;
		LATC3 = 0;
		break;
	}
	if (dir)
		step2Count++;
	else
		step2Count--;
}

