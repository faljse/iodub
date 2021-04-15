#ifndef ACTIONSETGROUP_H
#define ACTIONSETGROUP_H
#include <Controllino.h>
#include "action.h"
#include "actionset.h"


class ActionSetGroup;
class ActionSetGroup {
  
   public:
     uint8_t id;
     uint8_t actionset_idx_len;
     ActionSet *actionSet;
     uint8_t pos=0;

  ActionSetGroup(){};
  ActionSetGroup(uint8_t _id, uint8_t _actionset_len, ActionSet _actionSet[]): 
  id(_id),
  actionset_idx_len(_actionset_len),
  actionSet(_actionSet)
  {};

  void next() {
    Serial.println(pos);
    Serial.println(actionset_idx_len);
    pos=(pos+1)%actionset_idx_len;
    actionSet[pos].run();
  }
};
#endif