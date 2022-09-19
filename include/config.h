#ifndef CONFIG_H
#define CONFIG_H

#include <Controllino.h>
#include <PubSubClient.h>

#include "analogmultibutton.h"

#define COUNT_OF(x) ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))


void buildConfig();

extern PubSubClient *psclient;



extern const uint8_t buttons[46] PROGMEM;
extern const uint8_t relays[11] PROGMEM;
extern const uint8_t actions[11][10][10] PROGMEM;

extern const uint8_t dimmers[43] PROGMEM;


extern AnalogMultiButton abuttons[9];
extern uint8_t actionstate[20];


#endif