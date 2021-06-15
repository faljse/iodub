#ifndef ACTION_H
#define ACTION_H
#include <Controllino.h>
#include "relay.h"
#include "dimmer.h"


enum  CmdType{Off=0,On=1,Toggle=2,Dim=3};

class Action;
class Action {
  
   public:
     Dimmer *dimmer;
     Relay *relay;
     CmdType cmdType;
     uint8_t value=0;
     uint8_t pos=0;

   Action(){};
  Action(Dimmer *_dimmer, Relay *_relay, CmdType _cmdType, uint8_t _pos, uint8_t _value = 0): 
  dimmer(_dimmer),
  relay(_relay),
  pos(_pos),
  cmdType(_cmdType), 
  value(_value)
  {};

  void exec() {

    if(dimmer!=0) {
      dimmer->dim(value);
    }
   
    else if(relay!=0){
      relay->set(cmdType);
    }
  }
};
#endif