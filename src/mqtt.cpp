#include <SPI.h>
#include "config.h"
#include <string.h>


#include "mqtt.h"
#include "relay.h"
#include "dimmer.h"


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

        if(aidx>COUNT_OF(actionstate))
          return;
        uint8_t pos=actionstate[aidx];
        if(pgm_read_byte(&actions[aidx][pos][0])==0) {//terminating zero - reset to pos 0
          pos=0;
        }
        for(uint8_t i=0;i<10;i++) {
          uint8_t id=pgm_read_byte(&actions[aidx][pos][i*2]);  
          uint8_t val=pgm_read_byte(&actions[aidx][pos][i*2+1]);
          if(id==0) break;
          if(id<100) sendRelay(id, val);
          else sendDimmer(id, val);
        }
        actionstate[aidx]=pos+1;
    }
    


}
