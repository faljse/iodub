#ifndef RELAY_H
#define RELAY_H

#include <Controllino.h>

void sendRelay(uint8_t outputNr, uint8_t on) {
  digitalWrite(outputNr, on);
  char strNr[5];
  char strOn[4];
  snprintf(strNr, 10, "%d",outputNr);
  snprintf(strOn, 10, "%s",on?"ON":"OFF");
  Serial.print("send");
  Serial.print(strNr);
  Serial.println(strOn);
}

#endif