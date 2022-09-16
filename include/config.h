#ifndef CONFIG_H
#define CONFIG_H

#include <Controllino.h>
#include "analogmultibutton.h"


void buildConfig();

extern const uint8_t actions[5][10][10] PROGMEM;
extern const uint8_t relays[11] PROGMEM;

extern AnalogMultiButton abuttons[9];

#endif