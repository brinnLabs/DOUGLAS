/* 
 * File:   BasicScript.h
 * Author: Lance
 *
 * Created on July 1, 2015, 8:27 PM
 */

#ifndef BASICSCRIPT_H
#define	BASICSCRIPT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define FWD(_x_)  (_x_&0x3F)
#define REV(_x_) ((_x_&0x3F)|0x80)
#define RFWD(_x_) ((_x_&0x3F)|0x40)
#define RREV(_x_) ((_x_&0x3F)|0xC0)
    
#define MAX 0x1F
#define MAXSTEPS 3500
    
#define CMDREPEAT 4  // How many times to repeat each command
    
const uint8_t ScriptData[] = {
// Stepper 0    Stepper 1    
//    FWD(MAX),       REV(MAX),
//    REV(MAX),       FWD(MAX),
//    0,              REV(MAX),
//    0,              FWD(MAX),
//    REV(MAX),       0,
//    FWD(MAX),       0,
//    FWD(MAX),       REV(MAX),
//    REV(MAX),       FWD(MAX),
//    FWD(MAX),       FWD(MAX),
//    REV(MAX),       REV(MAX),
//    
//};
//
//uint8_t DummyScript[] = {
    REV(MAX/4),       REV(MAX/4),
    REV(MAX/2),       REV(MAX/2),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),  
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX/2),       REV(MAX/2),
    REV(MAX/4),       REV(MAX/4),  
    
    FWD(MAX/4),     FWD(MAX/4),
    FWD(MAX/2),     FWD(MAX/2),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    FWD(MAX),       FWD(MAX),
    
    FWD(MAX/2),       FWD(MAX/2),
    FWD(MAX/4),       FWD(MAX/4),  
    
    0,              0,
    0,              0,
    0,              0,
    0,              0,
    0,              0,
    
    
    REV(MAX/4),     REV(MAX/4),
    REV(MAX/2),     REV(MAX/2),
    
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),
    REV(MAX),       REV(MAX),    
    
    REV(MAX/2),       REV(MAX/2),
    REV(MAX/4),       REV(MAX/4),
    
    0,              0,
    0,              0,
    0,              0,
    0,              0,
    0,              0,
    
    REV(MAX/4),     FWD(MAX/4),
    REV(MAX/2),     FWD(MAX/2),
    
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    
    REV(MAX/2),     FWD(MAX/2),
    REV(MAX/4),     FWD(MAX/4),
    
    FWD(MAX/4),     REV(MAX/4),
    FWD(MAX/2),     REV(MAX/2),
    
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    FWD(MAX),       REV(MAX),
    
    FWD(MAX/2),     REV(MAX/2),
    FWD(MAX/4),     REV(MAX/4),
    
    REV(MAX/4),     FWD(MAX/4),
    REV(MAX/2),     FWD(MAX/2),
    
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    REV(MAX),       FWD(MAX),
    
    REV(MAX/2),     FWD(MAX/2),
    REV(MAX/4),     FWD(MAX/4),
};

const uint16_t ScriptSize = sizeof(ScriptData);
uint16_t ScriptLoc;

#ifdef	__cplusplus
}
#endif

#endif	/* BASICSCRIPT_H */

