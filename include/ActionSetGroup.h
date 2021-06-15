#ifndef ACTIONSETGROUP_H
#define ACTIONSETGROUP_H
#include <Controllino.h>
#include "actionset.h"
  boolean runPos(uint8_t pos);

class ActionSetGroup;
class ActionSetGroup {
  
   public:
     uint8_t id;
     uint8_t actions_len;
     Action *actions;
     uint8_t pos=1;

  ActionSetGroup(){};
  ActionSetGroup(uint8_t _id, uint8_t _actions_len, Action *_actions): 
  id(_id),
  actions_len(_actions_len),
  actions(_actions)
  {};

  void next() {
    pos=pos+1;
    Serial.print("pos: ");
    Serial.print(pos);
    Serial.print("/");
    if(!runPos(pos)){
      pos=1;
      runPos(pos);
    }
  }

  boolean runPos(uint8_t pos) {
    bool found=false;
    for(int i=0;i<actions_len;i++) {
      if(actions[i].pos==pos) {
        actions[i].exec();
        found=true;
      } 
    }
    return found;
  }
};
#endif