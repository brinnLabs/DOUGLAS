#include "xc.inc"

;declare as global for use in C source files
;GLOBAL _send_neopixel, _numPixBytes, _subPixSend, _numPixSend, _pixTemp, _neoTemp, _clusterTemp, _qPixels
GLOBAL _rnd, _random

;user-defined psect (delta parameter must equal 2)
psect asm_text, global, class=CODE, delta=2

_rnd:
    rlcf     _random, f
    swapf   _random, w
    andlw   0xE0
    rrcf     _random, f
    addwf   _random, w
    addwf   _random, w
    addwf   _random, w
    sublw   0x35
    movwf   _random
    return
;
    END 
