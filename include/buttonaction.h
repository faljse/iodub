#ifndef BUTTONACTION_H
#define BUTTONACTION_H
#include <Controllino.h>

class ButtonAction;
class ButtonAction {
  
   public:
     uint8_t button_id;
     uint8_t button_sub_id;
     uint8_t action_id;

  ButtonAction();
  ButtonAction(uint8_t _button_id, uint8_t _button_sub_id, uint8_t _action_id): 
  button_id(_button_id),
  button_sub_id(_button_sub_id),
  action_id(_action_id)
  {};
};
#endif