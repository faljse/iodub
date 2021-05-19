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

Relay relay[4];
Dimmer dimmer[2];
ActionSetGroup asg[4];
ActionSet as0[2];
Action actions0_0[2];
Action actions0_1[2];
ActionSet as1[2];
Action actions1_0[1];
Action actions1_1[1];
ActionSet as2[2];
Action actions2_0[1];
Action actions2_1[1];
ActionSet as3[2];
Action actions3_0[1];
Action actions3_1[1];
AnalogMultiButton buttons[2];
void buildConfig() {
relay[0] = Relay(1, CONTROLLINO_R0);
pinMode(CONTROLLINO_R0, OUTPUT);
relay[1] = Relay(2, CONTROLLINO_R1);
pinMode(CONTROLLINO_R1, OUTPUT);
relay[2] = Relay(3, CONTROLLINO_R2);
pinMode(CONTROLLINO_R2, OUTPUT);
relay[3] = Relay(4, CONTROLLINO_R4);
pinMode(CONTROLLINO_R4, OUTPUT);
dimmer[0] = Dimmer(1, 1);
dimmer[1] = Dimmer(2, 2);
actions0_0[0] = Action(0, &relay[0], CmdType::On);
actions0_0[1] = Action(&dimmer[0],0, CmdType::Dim, 100);
as0[0]=ActionSet(1, 2, actions0_0);
actions0_1[0] = Action(0, &relay[0], CmdType::Off);
actions0_1[1] = Action(&dimmer[0],0, CmdType::Dim);
as0[1]=ActionSet(1, 2, actions0_1);
asg[0]=ActionSetGroup(1, 2, as0);
actions1_0[0] = Action(0, &relay[1], CmdType::On);
as1[0]=ActionSet(1, 1, actions1_0);
actions1_1[0] = Action(0, &relay[1], CmdType::Off);
as1[1]=ActionSet(1, 1, actions1_1);
asg[1]=ActionSetGroup(2, 2, as1);
actions2_0[0] = Action(0, &relay[2], CmdType::Off);
as2[0]=ActionSet(1, 1, actions2_0);
actions2_1[0] = Action(0, &relay[2], CmdType::On);
as2[1]=ActionSet(1, 1, actions2_1);
asg[2]=ActionSetGroup(3, 2, as2);
actions3_0[0] = Action(0, &relay[3], CmdType::Off);
as3[0]=ActionSet(1, 1, actions3_0);
actions3_1[0] = Action(0, &relay[3], CmdType::On);
as3[1]=ActionSet(1, 1, actions3_1);
asg[3]=ActionSetGroup(4, 2, as3);
const int voltages[5] = {0, 111, 170, 232, 362};
const ActionSetGroup asg_b1[4] = {asg[0], asg[1], asg[2], asg[3]};
buttons[0] = AnalogMultiButton(CONTROLLINO_A0, 5, voltages, asg_b1, 20, 1024);
pinMode(CONTROLLINO_A0, INPUT);
const ActionSetGroup asg_b2[4] = {asg[0], asg[1], asg[2], asg[3]};
buttons[1] = AnalogMultiButton(CONTROLLINO_A1, 5, voltages, asg_b2, 20, 1024);
pinMode(CONTROLLINO_A1, INPUT);
}
#endif