#include <Controllino.h>


class Terminal;
class Terminal {
   public:
     uint8_t nr;
     uint8_t RoomNr;
     const char *name;

   
  Terminal(uint8_t _nr, uint8_t _RoomNr, const char *_name): 
  nr(_nr),
  RoomNr(_RoomNr),
  name(_name) {
  }
};