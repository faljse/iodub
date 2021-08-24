#ifndef CONFIG_H
#define CONFIG_H

#include <Controllino.h>
#include "dimmer.h"
#include "relay.h"
#include "action.h"
#include "actionset.h"
#include "actionsetgroup.h"
#include "analogmultibutton.h"
#include "buttonaction.h"


void buildConfig();


extern Relay relay[5];
const uint8_t relaySize=5;
extern Dimmer dimmer[22];
const uint8_t dimmerSize=22;

extern ActionSetGroup asg[9];
extern Action actions0[0];
extern Action actions1[2];
extern Action actions2[2];
extern Action actions3[2];
extern Action actions4[2];
extern Action actions5[2];
extern Action actions6[10];
extern Action actions7[44];
extern Action actions8[8];
extern AnalogMultiButton buttons[9];

#endif