/*
 * File:   stepper.h
 * Author: Dominic
 *
 * Created on September 25, 2015, 9:40 PM
 */

#ifndef STEPPER_H
#define	STEPPER_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif

	uint8_t step1Count, step2Count;
	void stepperInit(void);
	void stepper1Step(bool dir);
	void stepper2Step(bool dir);


#ifdef	__cplusplus
}
#endif

#endif	/* STEPPER_H */

