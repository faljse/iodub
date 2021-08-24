#include <SPI.h>
#include "config.h"
#include <string.h>


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
const String dimmerPath="home/light/dimmer/";
void callbackMQTT(char* _topic, byte* _payload, unsigned int length) {
        String topic = String(_topic);
        char ptmp[length+1];
        ptmp[length]='\0';
        memcpy(ptmp, _payload, length);
        String payload = String(ptmp);
      if(topic.startsWith(dimmerPath))
      {
        uint8_t id =  topic.substring(dimmerPath.length()).toInt();
        uint8_t value = payload.toInt();

        for(uint8_t i=0;i<dimmerSize;i++) {
            if(dimmer[i].id == id)
                dimmer[i].value = value;
                
        }
        Serial.print(id);
        Serial.print(value);
        Serial.println();
    }
    


}
