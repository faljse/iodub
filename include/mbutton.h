#ifndef MBUTTON_H
#define MBUTTON_H
#include <Controllino.h>

class MButton;
class MButton {
  
   public:
     uint8_t id;
     uint8_t output;

  MButton();
  MButton(uint8_t _id, uint8_t _output): 
  id(_id),
  output(_output)
  {};
};
#endif