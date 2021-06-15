#ifndef RELAY_H
#define RELAY_H

#include <Controllino.h>

class Relay;
class Relay{
   public:
     uint8_t id;
     boolean on = false;
     uint8_t inputNr;
     uint8_t outputNr;

  Relay(){};
  Relay(uint8_t _id, uint8_t _outputNr): 
  id(_id),
  outputNr(_outputNr)
   {
  }
  void set(boolean _on){
    on=_on;
    send();
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
    Serial.print("send");
    Serial.print(strNr);
    Serial.println(strOn);
  }
};
#endif