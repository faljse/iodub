#ifndef DIMMER_H
#define DIMMER_H
#include <Controllino.h>
#include "dmx.h"
#include "mqtt.h"



class Dimmer;
class Dimmer{
   public:
    uint8_t id;
    bool on = false;
    uint8_t ch;
    uint8_t value=0;

  Dimmer(){};
  Dimmer(uint8_t _id, uint8_t _ch): 
  id(_id),
  ch(_ch) 
   {
  }

  void dim(int _value){
    value=_value;
    writeDMX();
  }

  void writeDMX() {
    dmx_setch(ch,value);
  }

  void sendMQTT() {
    const char *topic="home/light/dimmer/000/state";
    const char *payload="000";
    sprintf((char *)topic, "home/light/dimmer/%d/stat1", id);
    sprintf((char *)payload, "%d", id);
    psclient->publish(topic, payload);

  }

};

#endif