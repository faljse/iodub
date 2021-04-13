#ifndef CONFIG_H
#define CONFIG_H

#include "light.h"
#include "dimmer.h"
#include "relay.h"
#include "dimmer.h"
#include "action.h"
#include "button.h"
#include "light.h"

Light *lights[5];
Action *actions[8];

void buildConfig() {

lights[0] = new Relay(1, CONTROLLINO_R0);
lights[1] = new Relay(2, CONTROLLINO_R1);
lights[2] = new Relay(3, CONTROLLINO_R2);
lights[3] = new Dimmer(4, 1);
lights[4] = new Dimmer(5, 2);
actions[0] = new Action(1, 0, CmdType::On);
actions[1] = new Action(1, 1, CmdType::On);
actions[2] = new Action(1, 3, CmdType::Dim, 100);
actions[3] = new Action(1, 4, CmdType::Dim, 100);
actions[4] = new Action(2, 0, CmdType::Off);
actions[5] = new Action(2, 1, CmdType::Off);
actions[6] = new Action(2, 3, CmdType::Dim);
actions[7] = new Action(2, 4, CmdType::Dim);

}






#endif

