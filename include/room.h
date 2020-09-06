#include <Controllino.h>

class Room;
class Room {
  public:
    const char *name;
    uint8_t nr;
    Room(uint8_t _nr, const char * _name):
      nr(_nr),
      name(_name){
    }

};