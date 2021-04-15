#ifndef DIMMER_H
#define DIMMER_H

#include <Controllino.h>
#include "dmx.h"

class Dimmer;
class Dimmer{
   public:
    uint8_t id;
    boolean on = false;
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
    dmx_set[ch] = value;
  }
};

#endif