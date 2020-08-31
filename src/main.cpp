#include <Controllino.h>
#include <JC_Button.h>
#include <EEPROM.h>
#include <SPI.h>
#include "light.h"
#include "room.h"
#include "terminal.h"
#include <string.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <NetEEPROM.h>
#include <dmx.h>


EthernetUDP Udp;

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

Terminal terminals[] = {
 Terminal(1, 1,"SalonTerminal"),
};
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

void setup()
{
  Serial.begin(19200);
  Serial.println("-----------------------------------------");
  Serial.println("");
  for(int i=0; i<(sizeof(lights)/sizeof(*lights)); i++) {
    lights[i].inputNr.begin();
  }
  // NetEeprom.begin();
  // Udp.begin(1717);
  dmx_init();
}

int dir=1;
int cnt=0;
void loop() {

  cnt++;
  if(cnt%1000==0) {
  	dmx_buffer[1]+=dir;
    if(dmx_buffer[1]>=50)
      dir=-1;
    if(dmx_buffer[1]==0)
      dir=1;
  }




//   int packetSize = Udp.parsePacket();
//   if(packetSize)
//   {
//     IPAddress remote = Udp.remoteIP();
//     uint16_t port = Udp.remotePort();
//     // read the packet into packetBufffer
//     Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
//     Udp.beginPacket(remote, port);
//     Udp.write("OK");
//     Udp.endPacket();
// }
}
