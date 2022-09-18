#include <Controllino.h>
#include "config.h"

void sendRelay(uint8_t id, uint8_t value) {
  char strNr[10];
  char strOn[10];
  snprintf(strNr, 10, "%d", 0);

  for(uint8_t i=0; i<(sizeof(relays)/2); i++) {
    uint8_t rid=pgm_read_byte(&(relays[i*2]));
    if(id==rid) {
        digitalWrite(pgm_read_byte(&(relays[i*2+1])), value);
        snprintf(strNr, 10, "%d", pgm_read_byte(&(relays[i*2+1])));
    }
  }
  snprintf(strOn, 10, "%s", value?"ON":"OFF");
  Serial.print("send");
  Serial.print(strNr);
  Serial.println(strOn);
}