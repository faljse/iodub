#ifndef ACTION_H
#define ACTION_H
#include <Controllino.h>
enum  CmdType{Off=0,On=1,Toggle=2,Dim=3};

class Action;
class Action {
  
   public:
     uint8_t actionset_id;
     uint8_t light_idx;
     CmdType cmdType;
     uint8_t value=0;

   Action();
  Action(uint8_t _actionset_id, uint8_t _light_idx, CmdType _cmdType, uint8_t _value = 0): 
  actionset_id(_actionset_id),
  light_idx(_light_idx),
  cmdType(_cmdType), 
  value(_value)
  {};
};
#endif