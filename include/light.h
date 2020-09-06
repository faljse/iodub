#include <Controllino.h>


class Light;
class Light {
   public:
     uint8_t nr;
     uint8_t RoomNr;
     boolean on = false;
     uint8_t inputNr;
     uint8_t outputNr;
     const char *name;

   
  Light(uint8_t _nr, uint8_t _RoomNr,boolean _on, uint8_t _inputNr, uint8_t _outputNr, const char *_name): 
  nr(_nr),
  RoomNr(_RoomNr),
  on(_on), 
  inputNr(_inputNr), 
  outputNr(_outputNr), 
  name(_name) {
  }

  void toggle() {
    on=!on;
  }
  
  void send() {
    digitalWrite(outputNr, on);
    char strNr[5];
    char strOn[4];
    snprintf(strNr, 10, "%d",outputNr);
    snprintf(strOn, 10, "%s",on?"ON":"OFF");
  }
};