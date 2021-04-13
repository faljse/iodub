#ifndef LIGHT_H
#define LIGHT_H
#include "action.h"
class Light;
class Light {
   public:
     uint8_t id;
     Light(uint8_t _id): id(_id){};
     virtual void cmd(Action *action) =0;
};
#endif