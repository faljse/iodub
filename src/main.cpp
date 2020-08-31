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
#define TLight 1
#define TDim 2
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))



EthernetUDP Udp;
void handlePacket();
void timer_init();


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
 Dimmer(1, 1,1,2,"Leds am Tisch"),
};

Terminal terminals[] = {
 Terminal(1, 1,"SalonTerminal"),
};
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

void setup()
{
  for(int i=0; i<COUNT_OF(lights); i++) {
    lights[i].inputNr.begin();
  }
  dmx_init();
  timer_init();
  Serial.begin(19200);
  Serial.println("--IODUB--");
  NetEeprom.begin();
  Udp.begin(1717);
}

int dir=1;
int cnt=0;
unsigned long time=0;
unsigned long td=0;

void timer_init() {
  TCCR1A = 0x00;      // Normal mode, => Disconnect Pin OC1  PWM Operation disabled
  TCCR1B = 0x02;      // 16MHz clock with prescaler, TCNT1 increments every .5 uS (cs11 bit set)
  OCR1A = 33333;   // = 16666 microseconds (each count is .5 us)
  TIMSK1 |= (1 << OCIE1A); //Bit Output Compare A Match Interrupt Enable setzen
}

ISR(TIMER1_COMPA_vect) {
  for(uint8_t i=0;i!=DMX_CHANNELS;i++) {
    if(dmx_cur[i]>dmx_set[i]) dmx_cur[i]--;
    if(dmx_cur[i]<dmx_set[i]) dmx_cur[i]++;
  }
  // Serial.println("set");
  // Serial.println(dmx_set[0]);
  // Serial.println(dmx_cur[0]);
}

void loop() {
  unsigned long tmp=millis();
  td=tmp-time;
  time=tmp;
  handlePacket();
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
