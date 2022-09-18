#ifndef CONFIG_H
#define CONFIG_H

#include <Controllino.h>
#include "analogmultibutton.h"


void buildConfig();

extern const uint8_t buttons[46] PROGMEM;
extern const uint8_t relays[11] PROGMEM;
extern const uint8_t dimmers[43] PROGMEM;

extern const uint8_t actions[5][10][10] PROGMEM;

extern AnalogMultiButton abuttons[9];
extern uint8_t actionstate[20];


#endif