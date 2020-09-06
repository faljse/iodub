#include <Controllino.h>
#include "dmx.h"

class Dimmer;
class Dimmer {
   public:
     uint8_t nr;
     uint8_t RoomNr;
     boolean on = false;
     uint8_t chWW;
     uint8_t valWW=0;
     uint8_t chCW;
     uint8_t valCW=0;
     const char *name;

  Dimmer(uint8_t _nr, uint8_t _RoomNr, uint8_t _chWW, uint8_t _chCW, const char *_name): 
  nr(_nr),
  RoomNr(_RoomNr),
  chWW(_chWW), 
  chCW(_chCW), 
  name(_name) {
  }

  void writeDMX() {
    dmx_set[chWW] = valWW;
    dmx_set[chCW] = valCW;
  }
};