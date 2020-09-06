#include <Controllino.h>
#include <JC_Button.h>


class RLaden;
class RLaden {
   public:
     uint8_t nr;
     uint8_t RoomNr;
     boolean on = false;
     uint8_t upNr;
     uint8_t downNr;
     const char *name;

   
  RLaden(uint8_t _nr, uint8_t _RoomNr,boolean _on, uint8_t _upNr, uint8_t _downNr, const char *_name): 
  nr(_nr),
  RoomNr(_RoomNr),
  on(_on), 
  upNr(_upNr), 
  downNr(_downNr), 
  name(_name) {
  }

  void up() {
  }

  void down() {
  }
};