#ifndef DIMMER_H
#define DIMMER_H

#include <Controllino.h>
#include "dmx.h"
#include <light.h>

class Dimmer;
class Dimmer : public Light{
   public:
     boolean on = false;
     uint8_t ch;
     uint8_t value=0;

  Dimmer(uint8_t _id, uint8_t _ch): 
  Light(_id),
  ch(_ch) 
   {
  }

  void cmd(Action *action){
    switch (action->cmdType)
    {
      case CmdType::Dim:
        value=action->value;
        break;
    }
  }

  void writeDMX() {
    dmx_set[ch] = value;
  }
};

#endif