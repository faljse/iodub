#ifndef LIGHT_H
#define LIGHT_H
class Light;
class Light {
   public:
     uint8_t id;
     Light(uint8_t _id): id(_id){};
     void cmd(uint8_t cmd, uint8_t value) {
         
     }
};
#endif