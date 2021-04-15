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

void buildConfig() {
Relay relay[3];
Dimmer dimmer[2];
relay[0] = Relay(1, CONTROLLINO_R0);
pinMode(CONTROLLINO_R0, OUTPUT);
relay[1] = Relay(2, CONTROLLINO_R1);
pinMode(CONTROLLINO_R1, OUTPUT);
relay[2] = Relay(3, CONTROLLINO_R2);
pinMode(CONTROLLINO_R2, OUTPUT);
dimmer[0] = Dimmer(1, 1);
dimmer[1] = Dimmer(2, 2);
ActionSetGroup asg[2];
Action actions0_0[4];
ActionSet as0_0[2];
actions0_0[0] = Action(&relay[0], CmdType::On);
actions0_0[1] = Action(&relay[1], CmdType::On);
actions0_0[2] = Action(&dimmer[0], CmdType::Dim, 100);
actions0_0[3] = Action(&dimmer[1], CmdType::Dim, 100);
as0_0[0]=ActionSet(1, 4, actions0_0);
Action actions0_1[4];
ActionSet as0_1[2];
actions0_1[0] = Action(&relay[0], CmdType::Off);
actions0_1[1] = Action(&relay[1], CmdType::Off);
actions0_1[2] = Action(&dimmer[0], CmdType::Dim);
actions0_1[3] = Action(&dimmer[1], CmdType::Dim);
as0_1[1]=ActionSet(1, 4, actions0_1);
asg[0]=ActionSetGroup(1, 2, as0_1);
Action actions1_0[1];
ActionSet as1_0[2];
as1_0[0]=ActionSet(1, 1, actions1_0);
Action actions1_1[3];
ActionSet as1_1[2];
as1_1[1]=ActionSet(1, 3, actions1_1);
asg[1]=ActionSetGroup(2, 2, as1_1);

}
#endif