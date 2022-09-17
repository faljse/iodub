
#include <Controllino.h>
#include "analogmultibutton.h"
#include "config.h"

AnalogMultiButton abuttons[9];

const uint8_t buttons[19] PROGMEM = {
1, CONTROLLINO_A0, 2, CONTROLLINO_A8, 3, CONTROLLINO_A6, 4, CONTROLLINO_A3, 5, CONTROLLINO_A7, 6, CONTROLLINO_A1, 7, CONTROLLINO_A4, 8, CONTROLLINO_A5, 9, CONTROLLINO_A2};
const uint8_t relays[11] PROGMEM = {
1, CONTROLLINO_R2, 2, CONTROLLINO_R1, 2, CONTROLLINO_R0, 4, CONTROLLINO_R3, 5, CONTROLLINO_R4};
const uint8_t dimmers[43] PROGMEM = {
101, 1, 102, 2, 103, 3, 104, 4, 105, 5, 106, 6, 107, 7, 108, 8, 109, 9, 110, 10, 112, 12, 113, 13, 114, 14, 115, 15, 116, 16, 117, 17, 118, 18, 119, 19, 120, 20, 121, 21, 122, 22};
const uint8_t actions[5][10][10] PROGMEM = {
{{1,0,2,0,0,0,0,0,0,0},{1,0,2,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}},{{3,0,4,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}}};


void buildConfig() {
    pinMode(CONTROLLINO_R4, OUTPUT);
    const int voltages[5] = {0, 111, 170, 232, 362};
    for(uint8_t i=0; i<(sizeof(buttons)/2);i++) {
        uint8_t pin=pgm_read_byte(&(buttons[i*2]));
        uint8_t aidx=pgm_read_byte(&(buttons[i*2+1]));

        abuttons[i] = AnalogMultiButton(pin, 5, voltages, aidx, 20, 1024);
        pinMode(pgm_read_byte(&(buttons[i*2]))+1, INPUT);
    }
}