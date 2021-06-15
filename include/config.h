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

Relay relay[5];
Dimmer dimmer[2];
ActionSetGroup asg[6];
Action actions0[0];
Action actions1[2];
Action actions2[2];
Action actions3[2];
Action actions4[2];
Action actions5[2];
AnalogMultiButton buttons[9];
void buildConfig() {
relay[0] = Relay(1, CONTROLLINO_R0);
pinMode(CONTROLLINO_R0, OUTPUT);
relay[1] = Relay(2, CONTROLLINO_R1);
pinMode(CONTROLLINO_R1, OUTPUT);
relay[2] = Relay(3, CONTROLLINO_R2);
pinMode(CONTROLLINO_R2, OUTPUT);
relay[3] = Relay(4, CONTROLLINO_R3);
pinMode(CONTROLLINO_R3, OUTPUT);
relay[4] = Relay(5, CONTROLLINO_R4);
pinMode(CONTROLLINO_R4, OUTPUT);
dimmer[0] = Dimmer(1, 1);
dimmer[1] = Dimmer(2, 2);
asg[0]=ActionSetGroup(0, 0, actions0);
actions1[0] = Action(0, &relay[0], CmdType::On, 1);
actions1[1] = Action(0, &relay[0], CmdType::Off, 2);
asg[1]=ActionSetGroup(1, 2, actions1);
actions2[0] = Action(0, &relay[1], CmdType::On, 1);
actions2[1] = Action(0, &relay[1], CmdType::Off, 2);
asg[2]=ActionSetGroup(2, 2, actions2);
actions3[0] = Action(0, &relay[2], CmdType::Off, 1);
actions3[1] = Action(0, &relay[2], CmdType::On, 2);
asg[3]=ActionSetGroup(3, 2, actions3);
actions4[0] = Action(0, &relay[3], CmdType::Off, 1);
actions4[1] = Action(0, &relay[3], CmdType::On, 2);
asg[4]=ActionSetGroup(4, 2, actions4);
actions5[0] = Action(0, &relay[4], CmdType::Off, 1);
actions5[1] = Action(0, &relay[4], CmdType::On, 2);
asg[5]=ActionSetGroup(5, 2, actions5);
const int voltages[5] = {0, 111, 170, 232, 362};
const ActionSetGroup asg_b1[4] = {asg[3], asg[0], asg[0], asg[0]};
buttons[0] = AnalogMultiButton(CONTROLLINO_A0, 5, voltages, asg_b1, 20, 1024);
pinMode(CONTROLLINO_A0, INPUT);
const ActionSetGroup asg_b2[4] = {asg[3], asg[0], asg[0], asg[0]};
buttons[1] = AnalogMultiButton(CONTROLLINO_A8, 5, voltages, asg_b2, 20, 1024);
pinMode(CONTROLLINO_A8, INPUT);
const ActionSetGroup asg_b3[4] = {asg[1], asg[0], asg[0], asg[0]};
buttons[2] = AnalogMultiButton(CONTROLLINO_A6, 5, voltages, asg_b3, 20, 1024);
pinMode(CONTROLLINO_A6, INPUT);
const ActionSetGroup asg_b4[4] = {asg[2], asg[0], asg[0], asg[0]};
buttons[3] = AnalogMultiButton(CONTROLLINO_A3, 5, voltages, asg_b4, 20, 1024);
pinMode(CONTROLLINO_A3, INPUT);
const ActionSetGroup asg_b5[4] = {asg[0], asg[0], asg[0], asg[0]};
buttons[4] = AnalogMultiButton(CONTROLLINO_A7, 5, voltages, asg_b5, 20, 1024);
pinMode(CONTROLLINO_A7, INPUT);
const ActionSetGroup asg_b6[4] = {asg[5], asg[0], asg[0], asg[0]};
buttons[5] = AnalogMultiButton(CONTROLLINO_A1, 5, voltages, asg_b6, 20, 1024);
pinMode(CONTROLLINO_A1, INPUT);
const ActionSetGroup asg_b7[4] = {asg[5], asg[0], asg[0], asg[0]};
buttons[6] = AnalogMultiButton(CONTROLLINO_A4, 5, voltages, asg_b7, 20, 1024);
pinMode(CONTROLLINO_A4, INPUT);
const ActionSetGroup asg_b8[4] = {asg[0], asg[0], asg[0], asg[0]};
buttons[7] = AnalogMultiButton(CONTROLLINO_A5, 5, voltages, asg_b8, 20, 1024);
pinMode(CONTROLLINO_A5, INPUT);
const ActionSetGroup asg_b9[4] = {asg[4], asg[0], asg[0], asg[0]};
buttons[8] = AnalogMultiButton(CONTROLLINO_A2, 5, voltages, asg_b9, 20, 1024);
pinMode(CONTROLLINO_A2, INPUT);
}
#endif