#ifndef RELAY_H
#define RELAY_H

#include <Controllino.h>
#include <light.h>
class Relay;
class Relay : public Light{
   public:
     boolean on = false;
     uint8_t inputNr;
     uint8_t outputNr;

   
  Relay(uint8_t _id, uint8_t _outputNr): 
  Light(_id),
  outputNr(_outputNr)
   {
  }
  void cmd(Action *action){
    switch (action->cmdType)
    {
      case CmdType::On:
        on=true;
        break;
      case CmdType::Off:
        on=false;
        break;
      case CmdType::Toggle:
        on=!on;
        break;
    }
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
#endif