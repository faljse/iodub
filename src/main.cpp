#include <Controllino.h>
#include <JC_Button.h>
#include <EEPROM.h>
#include <SPI.h>
#include "light.h"
#include "room.h"
#include "terminal.h"
#include "dimmer.h"
#include <string.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <NetEEPROM.h>
#include <dmx.h>
#include "MyFreeRTOSConfig.h"
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include "rtostools.h"

#define TLight 1
#define TDim 2
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))



EthernetUDP Udp;
void handlePacket();
void timer_init();
void printTasks();
void TaskMixer(void *pvParameters);
void TaskNetwork(void *pvParameters);


Room room[] = {
  Room(1, "Salon"),
  Room(2, "Miranda"),
  Room(3, "Kueche"),
  Room(4, "BadUnten"),
  Room(5, "BadOben"),
};

Light lights[] = {
 Light(1, 1,false, CONTROLLINO_A0, CONTROLLINO_D11, "Lampe"),
 Light(2, 2,false, CONTROLLINO_A1, CONTROLLINO_D11, "Lampe"),
 Light(3, 2,false, CONTROLLINO_A1, CONTROLLINO_D11, "Lampe"),
 Light(4, 2,false, CONTROLLINO_A1, CONTROLLINO_D11, "Lampe") 
};

Dimmer dimmers[] = {
 Dimmer(1, 1,1,2,"Leds am Tisch1"),
  Dimmer(2, 1,3,4,"Leds am Tisch2")

};

Terminal terminals[] = {
 Terminal(1, 1,"SalonTerminal"),
};
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,


TaskHandle_t taskMixerHandle, taskNetworkHandle;

void setup()
{
  for(int i=0; i<COUNT_OF(lights); i++) {
    lights[i].inputNr.begin();
  }
  dmx_init();
  Serial.begin(19200);
  Serial.println("--IODUB--");
  NetEeprom.begin();
  Udp.begin(1717);

  xTaskCreate(TaskMixer, // Task function
              "Mixer", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              &taskMixerHandle); // Task handler

  xTaskCreate(TaskNetwork, // Task function
              "Network", // Task name
              128, // Stack size 
              NULL, 
              0, // Priority
              &taskNetworkHandle); // Task handler
}

int dir=1;
int cnt=0;
unsigned long time=0;
unsigned long td=0;

int8_t sgn(int8_t x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

void TaskMixer(void *pvParameters)
{
  for(;;) {
    for(uint8_t i=0;i!=DMX_CHANNELS;i++) {
      int16_t diff=dmx_set[i]-dmx_cur[i];
      dmx_cur[i]=dmx_cur[i]+diff;
    }
    delay(10);
  }
  
}

void TaskNetwork(void *pvParameters)
{
  for(;;) {
    handlePacket();
  }
}

void loop() {
  delay(3000);
  printTasks();
}

char ptrTaskList[250];
void printTasks() {
    vTaskList(ptrTaskList);
    Serial.println(F("**********************************"));
    Serial.println(F("Task  State   Prio    Stack    Num")); 
    Serial.println(F("**********************************"));
    Serial.print(ptrTaskList);
    Serial.println(F("**********************************"));
}

void handlePacket() {
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    IPAddress remote = Udp.remoteIP();
    uint16_t port = Udp.remotePort();
    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);    
    switch (packetBuffer[1])
    {
    case TLight:
      break;
    case TDim:
      for(uint8_t i=0; i!=COUNT_OF(dimmers); i++) {
        Dimmer &d=dimmers[i];
        uint8_t id=packetBuffer[2];
        if(d.nr==id){
          uint8_t chanNr = packetBuffer[3];
          uint8_t brightVal = packetBuffer[4];
          if(chanNr==0)
            d.valWW=brightVal;
          if(chanNr==1)
            d.valCW=brightVal;
          d.writeDMX();
          Udp.beginPacket(remote, port);
          Udp.write("OK");
          Udp.endPacket();
        }

      }
      break; 
    default:
          Udp.beginPacket(remote, port);
          Udp.write("NOK");
          Udp.endPacket();
      break;
    }
  }
}
