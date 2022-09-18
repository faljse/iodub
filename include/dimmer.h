#ifndef DIMMER_H
#define DIMMER_H
#include <Controllino.h>
#include "dmx.h"
#include "mqtt.h"
#include "config.h"

void writeDMX(uint8_t ch, uint8_t value);
void sendDimmer(int id, int value);
void sendMQTT(uint8_t id, uint8_t value);

#endif