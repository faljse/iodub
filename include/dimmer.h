#ifndef DIMMER_H
#define DIMMER_H
#include <Controllino.h>
#include "dmx.h"
#include "mqtt.h"
#include "config.h"

void writeDMX(uint8_t ch, uint8_t value) {
  dmx_setch(ch,value);
}
void sendDimmer(int id, int value){
  for(int i=0;i<(sizeof(relays)/2);i++) {
    uint8_t rid=pgm_read_byte(&(relays[i/2]));
    if(id==rid)
      writeDMX(pgm_read_byte(&(relays[i/2+1])), value);
  }
}



void sendMQTT(uint8_t id, uint8_t value) {
  const char *topic="home/light/dimmer/000/state";
  const char *payload="000";
  sprintf((char *)topic, "home/light/dimmer/%d/stat1", id);
  sprintf((char *)payload, "%d", value);
  psclient->publish(topic, payload);

}

#endif