#include <SPI.h>
#include "config.h"
#include <string.h>


#include "mqtt.h"
#include "relay.h"
#include "dimmer.h"
#include "action.h"



void reconnectMQTT(PubSubClient *psc) {
  // Loop until we're reconnected
  while (!psc->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (psc->connect("arduinoClient")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(psc->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
const String dimmerPath="home/action/";
void callbackMQTT(char* _topic, byte* _payload, unsigned int length) {
        String topic = String(_topic);
        char ptmp[length+1];
        ptmp[length]='\0';
        memcpy(ptmp, _payload, length);
        String payload = String(ptmp);
      if(topic.startsWith(dimmerPath))
      {
        String subTopic =  topic.substring(dimmerPath.length());
        int8_t slashIdx=subTopic.indexOf('/');
        if(slashIdx==-1)
          return;
        uint8_t aidx=subTopic.substring(0,slashIdx).toInt();
        String state=subTopic.substring(slashIdx);
        if(state.compareTo("/set")!= 0)
          return;
        Serial.print(aidx);
        Serial.print(":");
        Serial.print(payload.toInt());
        sendAction(aidx);

    }
    


}
