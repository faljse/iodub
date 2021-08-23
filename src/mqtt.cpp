#include <SPI.h>

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

void callbackMQTT(char* topic, byte* payload, unsigned int length) {
    Serial.print(topic);
    Serial.println();

}
