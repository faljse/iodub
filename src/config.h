#ifndef CONFIG_H
#define CONFIG_H

#include <Controllino.h>
#include "light.h"
#include "dimmer.h"
#include "relay.h"
#include "action.h"
#include "mbutton.h"
#include "buttonaction.h"

Light *lights[5];
Action *actions[8];
MButton *buttons[1];
ButtonAction *buttonactions[4];

void buildConfig() {
lights[0] = new Relay(1, CONTROLLINO_R0);
pinMode(CONTROLLINO_R0, OUTPUT);
lights[1] = new Relay(2, CONTROLLINO_R1);
pinMode(CONTROLLINO_R1, OUTPUT);
lights[2] = new Relay(3, CONTROLLINO_R2);
pinMode(CONTROLLINO_R2, OUTPUT);

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
buttons[0] = new MButton(1, CONTROLLINO_A0);
buttonactions[0] = new ButtonAction(1, 0, 1);
buttonactions[1] = new ButtonAction(1, 1, 2);
buttonactions[2] = new ButtonAction(1, 2, 1);
buttonactions[3] = new ButtonAction(1, 3, 2);
}
#endif