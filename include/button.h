#ifndef BUTTON_H
#define BUTTON_H
#include <Controllino.h>

class Button;
class Button {
  
   public:
     uint8_t id;
     uint8_t output;

  Button();
  Button(uint8_t _id, uint8_t _output): 
  id(_id),
  output(_output)
  {};
};
#endif