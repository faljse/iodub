#ifndef CONFIG_H
#define CONFIG_H

#include "light.h"
#include "dimmer.h"
#include "relay.h"
#include "dimmer.h"
#include "action.h"
#include "light.h"

Light *lights[4];
Action *actions[2];

void buildConfig() {
lights[0] = new Relay(1, CONTROLLINO_R0);
lights[1] = new Relay(2, CONTROLLINO_R0);
lights[2] = new Dimmer(3, 1);
lights[3] = new Dimmer(4, 2);

actions[0]=new Action(1,1,CmdType::On);

}






#endif

