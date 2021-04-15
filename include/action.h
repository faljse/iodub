#ifndef ACTION_H
#define ACTION_H
#include <Controllino.h>
#include "light.h"


enum  CmdType{Off=0,On=1,Toggle=2,Dim=3};

class Light;
class Action;
class Action {
  
   public:
     void *light;
     CmdType cmdType;
     uint8_t value=0;

   Action(){};
  Action(Light *light, CmdType _cmdType, uint8_t _value = 0): 
  light(light),
  cmdType(_cmdType), 
  value(_value)
  {};
};
#endif