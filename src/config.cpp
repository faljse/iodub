
#include <Controllino.h>
#include "analogmultibutton.h"
#include "config.h"

AnalogMultiButton abuttons[9];

const uint8_t buttons[46] PROGMEM = {
0,0,0,0, CONTROLLINO_A0, 1,1,1,1, CONTROLLINO_A8, 2,2,2,2, CONTROLLINO_A6, 3,3,3,3, CONTROLLINO_A3, 4,4,4,4, CONTROLLINO_A7, 0,0,0,0, CONTROLLINO_A1, 0,0,0,0, CONTROLLINO_A4, 0,0,0,0, CONTROLLINO_A5, 0,0,0,0, CONTROLLINO_A2};
const uint8_t relays[11] PROGMEM = {
1, CONTROLLINO_R2, 2, CONTROLLINO_R1, 2, CONTROLLINO_R0, 4, CONTROLLINO_R3, 5, CONTROLLINO_R4};
const uint8_t dimmers[43] PROGMEM = {
101, 1, 102, 2, 103, 3, 104, 4, 105, 5, 106, 6, 107, 7, 108, 8, 109, 9, 110, 10, 112, 12, 113, 13, 114, 14, 115, 15, 116, 16, 117, 17, 118, 18, 119, 19, 120, 20, 121, 21, 122, 22};
const uint8_t actions[11][10][10] PROGMEM = {
{{1,0,0,0,0,0,0,0,0,0},{1,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}},{{2,0,0,0,0,0,0,0,0,0},{2,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}},{{3,0,0,0,0,0,0,0,0,0},{3,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}},{{4,0,0,0,0,0,0,0,0,0},{4,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}},{{5,0,0,0,0,0,0,0,0,0},{5,1,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}}};
uint8_t actionstate[20];


void buildConfig() {
    for(uint8_t i=0; i<(sizeof(relays)/2);i++) {
        pinMode(pgm_read_byte(&(relays[i*2+1])), OUTPUT);
    }

    const int voltages[5] = {0, 111, 170, 232, 362};
    for(uint8_t i=0; i<(sizeof(buttons)/5);i++) {
        uint8_t pin=pgm_read_byte(&(buttons[i*5]));
        
        uint8_t aidx[4];
        aidx[0]=pgm_read_byte(&(buttons[i*5+1]));  
        aidx[1]=pgm_read_byte(&(buttons[i*5+2]));  
        aidx[2]=pgm_read_byte(&(buttons[i*5+3]));  
        aidx[3]=pgm_read_byte(&(buttons[i*5+4]));  



        abuttons[i] = AnalogMultiButton(pin, 5, voltages, aidx, 20, 1024);
        pinMode(pgm_read_byte(&(buttons[i*2+1])), INPUT);
    }
}