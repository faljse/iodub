#ifndef ACTIONSET_H
#define ACTIONSET_H
#include <Controllino.h>
#include "action.h"

class ActionSet;
class ActionSet {
  
   public:
     uint8_t id=0;
     uint8_t actions_idx_len=0;
     Action *actions;

  ActionSet(){};
  ActionSet(uint8_t _id, uint8_t _actions_len, Action _actions[]): 
  id(_id),
  actions_idx_len(_actions_len),
  actions(_actions)
  {};

  void run(){
    for(int i=0;i<actions_idx_len;i++) {
       actions[i].exec();
    }
  }
};
#endif