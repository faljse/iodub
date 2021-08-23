#ifndef MQTT_H
#define MQTT_H
#include <Ethernet.h>
#include <PubSubClient.h>
void reconnectMQTT(PubSubClient *psc);
void callbackMQTT(char* topic, byte* payload, unsigned int length);


#endif