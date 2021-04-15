#ifndef CONFIG_H
#define CONFIG_H

#include <Controllino.h>
#include "dimmer.h"
#include "relay.h"
#include "action.h"
#include "actionset.h"
#include "actionsetgroup.h"
#include "mbutton.h"
#include "buttonaction.h"

Relay relay[3];
Dimmer dimmer[2];
ActionSetGroup asg[2];
ActionSet as0[2];
Action actions0_0[4];
Action actions0_1[4];
ActionSet as1[2];
Action actions1_0[1];
Action actions1_1[3];
void buildConfig() {
relay[0] = Relay(1, CONTROLLINO_R0);
pinMode(CONTROLLINO_R0, OUTPUT);
relay[1] = Relay(2, CONTROLLINO_R1);
pinMode(CONTROLLINO_R1, OUTPUT);
relay[2] = Relay(3, CONTROLLINO_R2);
pinMode(CONTROLLINO_R2, OUTPUT);
dimmer[0] = Dimmer(1, 1);
dimmer[1] = Dimmer(2, 2);
actions0_0[0] = Action(0, &relay[0], CmdType::On);
actions0_0[1] = Action(0, &relay[1], CmdType::On);
actions0_0[2] = Action(&dimmer[0],0, CmdType::Dim, 100);
actions0_0[3] = Action(&dimmer[1],0, CmdType::Dim, 100);
as0[0]=ActionSet(1, 4, actions0_0);
actions0_1[0] = Action(0, &relay[0], CmdType::Off);
actions0_1[1] = Action(0, &relay[1], CmdType::Off);
actions0_1[2] = Action(&dimmer[0],0, CmdType::Dim);
actions0_1[3] = Action(&dimmer[1],0, CmdType::Dim);
as0[1]=ActionSet(1, 4, actions0_1);
asg[0]=ActionSetGroup(1, 2, as0);
as1[0]=ActionSet(1, 1, actions1_0);
as1[1]=ActionSet(1, 3, actions1_1);
asg[1]=ActionSetGroup(2, 2, as1);

}
#endif