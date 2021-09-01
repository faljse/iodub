#ifndef DATA_H
#define DATA_H
#include <Controllino.h>
struct ButtonS{
    uint8_t id;
    uint8_t inputNr;
    uint8_t sequence_A;
    uint8_t sequence_B;
    uint8_t sequence_C;
    uint8_t sequence_D;

};
struct ButtonS PROGMEM const mystruct[] = {{ 1,1,1,1,1,1 }};


#endif