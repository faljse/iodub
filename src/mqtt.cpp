#include <SPI.h>
#include <string.h>
#include <config.h>


#include "mqtt.h"

void reconnectMQTT(PubSubClient *psc) {
  // Loop until we're reconnected
  while (!psc->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (psc->connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      psc->publish("outTopic","hello world");
      // ... and resubscribe
      psc->subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(psc->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
const char* dimmerPath="home/light/dimmer/";
void callbackMQTT(char* topic, byte* payload, unsigned int length) {
    if (strncmp(topic, dimmerPath, strlen(dimmerPath)-1)==0)
    {
        uint8_t tLength = strlen(topic);
        if(tLength <= strlen(dimmerPath))
            return;
        uint8_t id = atoi(topic + strlen(dimmerPath));
        char valStr[length + 1];
        valStr[length + 1] = '\n';
        memcpy(valStr, payload, length);
        uint8_t value = atoi(valStr);

        for(uint8_t i=0;i<dimmerSize;i++) {
            if(dimmer[i].id == id)
                dimmer[i].value = value;
                
        }
        Serial.print(value);
        Serial.println();
    }
    


}
