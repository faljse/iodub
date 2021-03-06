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
Dimmer dimmer[22];
ActionSetGroup asg[9];
Action actions0[0];
Action actions1[2];
Action actions2[2];
Action actions3[2];
Action actions4[2];
Action actions5[2];
Action actions6[10];
Action actions7[44];
Action actions8[8];
AnalogMultiButton buttons[9];
void buildConfig() {
relay[0] = Relay(1, CONTROLLINO_R2);
pinMode(CONTROLLINO_R2, OUTPUT);
relay[1] = Relay(2, CONTROLLINO_R1);
pinMode(CONTROLLINO_R1, OUTPUT);
relay[2] = Relay(3, CONTROLLINO_R0);
pinMode(CONTROLLINO_R0, OUTPUT);
relay[3] = Relay(4, CONTROLLINO_R3);
pinMode(CONTROLLINO_R3, OUTPUT);
relay[4] = Relay(5, CONTROLLINO_R4);
pinMode(CONTROLLINO_R4, OUTPUT);
dimmer[0] = Dimmer(1, 1);
dimmer[1] = Dimmer(2, 2);
dimmer[2] = Dimmer(3, 3);
dimmer[3] = Dimmer(4, 4);
dimmer[4] = Dimmer(5, 5);
dimmer[5] = Dimmer(6, 6);
dimmer[6] = Dimmer(7, 7);
dimmer[7] = Dimmer(8, 8);
dimmer[8] = Dimmer(9, 9);
dimmer[9] = Dimmer(10, 10);
dimmer[10] = Dimmer(11, 11);
dimmer[11] = Dimmer(12, 12);
dimmer[12] = Dimmer(13, 13);
dimmer[13] = Dimmer(14, 14);
dimmer[14] = Dimmer(15, 15);
dimmer[15] = Dimmer(16, 16);
dimmer[16] = Dimmer(17, 17);
dimmer[17] = Dimmer(18, 18);
dimmer[18] = Dimmer(19, 19);
dimmer[19] = Dimmer(20, 20);
dimmer[20] = Dimmer(21, 21);
dimmer[21] = Dimmer(22, 22);
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
actions6[0] = Action(0, &relay[0], CmdType::On, 1);
actions6[1] = Action(0, &relay[0], CmdType::Off, 2);
actions6[2] = Action(0, &relay[1], CmdType::On, 2);
actions6[3] = Action(0, &relay[1], CmdType::Off, 3);
actions6[4] = Action(0, &relay[2], CmdType::On, 3);
actions6[5] = Action(0, &relay[2], CmdType::Off, 4);
actions6[6] = Action(0, &relay[3], CmdType::On, 4);
actions6[7] = Action(0, &relay[3], CmdType::Off, 5);
actions6[8] = Action(0, &relay[4], CmdType::On, 5);
actions6[9] = Action(0, &relay[4], CmdType::Off, 6);
asg[6]=ActionSetGroup(6, 10, actions6);
actions7[0] = Action(&dimmer[0],0, CmdType::Dim, 1, 100);
actions7[1] = Action(&dimmer[0],0, CmdType::Dim, 2, 0);
actions7[2] = Action(&dimmer[1],0, CmdType::Dim, 2, 100);
actions7[3] = Action(&dimmer[1],0, CmdType::Dim, 3, 0);
actions7[4] = Action(&dimmer[2],0, CmdType::Dim, 3, 100);
actions7[5] = Action(&dimmer[2],0, CmdType::Dim, 4, 0);
actions7[6] = Action(&dimmer[3],0, CmdType::Dim, 4, 100);
actions7[7] = Action(&dimmer[3],0, CmdType::Dim, 5, 0);
actions7[8] = Action(&dimmer[4],0, CmdType::Dim, 5, 100);
actions7[9] = Action(&dimmer[4],0, CmdType::Dim, 6, 0);
actions7[10] = Action(&dimmer[5],0, CmdType::Dim, 6, 100);
actions7[11] = Action(&dimmer[5],0, CmdType::Dim, 7, 0);
actions7[12] = Action(&dimmer[6],0, CmdType::Dim, 7, 100);
actions7[13] = Action(&dimmer[6],0, CmdType::Dim, 8, 0);
actions7[14] = Action(&dimmer[7],0, CmdType::Dim, 8, 100);
actions7[15] = Action(&dimmer[7],0, CmdType::Dim, 9, 0);
actions7[16] = Action(&dimmer[8],0, CmdType::Dim, 9, 100);
actions7[17] = Action(&dimmer[8],0, CmdType::Dim, 10, 0);
actions7[18] = Action(&dimmer[9],0, CmdType::Dim, 10, 100);
actions7[19] = Action(&dimmer[9],0, CmdType::Dim, 11, 0);
actions7[20] = Action(&dimmer[10],0, CmdType::Dim, 11, 100);
actions7[21] = Action(&dimmer[10],0, CmdType::Dim, 12, 0);
actions7[22] = Action(&dimmer[11],0, CmdType::Dim, 12, 100);
actions7[23] = Action(&dimmer[11],0, CmdType::Dim, 13, 0);
actions7[24] = Action(&dimmer[12],0, CmdType::Dim, 13, 100);
actions7[25] = Action(&dimmer[12],0, CmdType::Dim, 14, 0);
actions7[26] = Action(&dimmer[13],0, CmdType::Dim, 14, 100);
actions7[27] = Action(&dimmer[13],0, CmdType::Dim, 15, 0);
actions7[28] = Action(&dimmer[14],0, CmdType::Dim, 15, 100);
actions7[29] = Action(&dimmer[14],0, CmdType::Dim, 16, 0);
actions7[30] = Action(&dimmer[15],0, CmdType::Dim, 16, 100);
actions7[31] = Action(&dimmer[15],0, CmdType::Dim, 17, 0);
actions7[32] = Action(&dimmer[16],0, CmdType::Dim, 17, 100);
actions7[33] = Action(&dimmer[16],0, CmdType::Dim, 18, 0);
actions7[34] = Action(&dimmer[17],0, CmdType::Dim, 18, 100);
actions7[35] = Action(&dimmer[17],0, CmdType::Dim, 19, 0);
actions7[36] = Action(&dimmer[18],0, CmdType::Dim, 19, 100);
actions7[37] = Action(&dimmer[18],0, CmdType::Dim, 20, 0);
actions7[38] = Action(&dimmer[19],0, CmdType::Dim, 20, 100);
actions7[39] = Action(&dimmer[19],0, CmdType::Dim, 21, 0);
actions7[40] = Action(&dimmer[20],0, CmdType::Dim, 21, 100);
actions7[41] = Action(&dimmer[20],0, CmdType::Dim, 22, 0);
actions7[42] = Action(&dimmer[21],0, CmdType::Dim, 22, 100);
actions7[43] = Action(&dimmer[21],0, CmdType::Dim, 23, 0);
asg[7]=ActionSetGroup(7, 44, actions7);
actions8[0] = Action(&dimmer[7],0, CmdType::Dim, 1, 0);
actions8[1] = Action(&dimmer[8],0, CmdType::Dim, 1, 0);
actions8[2] = Action(&dimmer[7],0, CmdType::Dim, 2, 0);
actions8[3] = Action(&dimmer[8],0, CmdType::Dim, 2, 5);
actions8[4] = Action(&dimmer[7],0, CmdType::Dim, 3, 0);
actions8[5] = Action(&dimmer[8],0, CmdType::Dim, 3, 200);
actions8[6] = Action(&dimmer[7],0, CmdType::Dim, 4, 200);
actions8[7] = Action(&dimmer[8],0, CmdType::Dim, 4, 200);
asg[8]=ActionSetGroup(8, 8, actions8);
const int voltages[5] = {0, 111, 170, 232, 362};
const ActionSetGroup *asg_b1[4] = {&asg[3], &asg[0], &asg[0], &asg[0]};
buttons[0] = AnalogMultiButton(CONTROLLINO_A0, 5, voltages, asg_b1, 20, 1024);
pinMode(CONTROLLINO_A0, INPUT);
const ActionSetGroup *asg_b2[4] = {&asg[3], &asg[0], &asg[0], &asg[0]};
buttons[1] = AnalogMultiButton(CONTROLLINO_A8, 5, voltages, asg_b2, 20, 1024);
pinMode(CONTROLLINO_A8, INPUT);
const ActionSetGroup *asg_b3[4] = {&asg[1], &asg[0], &asg[0], &asg[0]};
buttons[2] = AnalogMultiButton(CONTROLLINO_A6, 5, voltages, asg_b3, 20, 1024);
pinMode(CONTROLLINO_A6, INPUT);
const ActionSetGroup *asg_b4[4] = {&asg[2], &asg[0], &asg[0], &asg[0]};
buttons[3] = AnalogMultiButton(CONTROLLINO_A3, 5, voltages, asg_b4, 20, 1024);
pinMode(CONTROLLINO_A3, INPUT);
const ActionSetGroup *asg_b5[4] = {&asg[8], &asg[6], &asg[7], &asg[0]};
buttons[4] = AnalogMultiButton(CONTROLLINO_A7, 5, voltages, asg_b5, 20, 1024);
pinMode(CONTROLLINO_A7, INPUT);
const ActionSetGroup *asg_b6[4] = {&asg[5], &asg[0], &asg[0], &asg[0]};
buttons[5] = AnalogMultiButton(CONTROLLINO_A1, 5, voltages, asg_b6, 20, 1024);
pinMode(CONTROLLINO_A1, INPUT);
const ActionSetGroup *asg_b7[4] = {&asg[5], &asg[0], &asg[0], &asg[0]};
buttons[6] = AnalogMultiButton(CONTROLLINO_A4, 5, voltages, asg_b7, 20, 1024);
pinMode(CONTROLLINO_A4, INPUT);
const ActionSetGroup *asg_b8[4] = {&asg[0], &asg[0], &asg[0], &asg[0]};
buttons[7] = AnalogMultiButton(CONTROLLINO_A5, 5, voltages, asg_b8, 20, 1024);
pinMode(CONTROLLINO_A5, INPUT);
const ActionSetGroup *asg_b9[4] = {&asg[4], &asg[0], &asg[0], &asg[0]};
buttons[8] = AnalogMultiButton(CONTROLLINO_A2, 5, voltages, asg_b9, 20, 1024);
pinMode(CONTROLLINO_A2, INPUT);
}
#endif