
#include <Controllino.h>
#include <JC_Button.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Ethernet.h>
#include <NetEEPROM.h>
#include <PubSubClient.h>
#include <string.h>


char macstr[18];
class Light;

// Update these with values suitable for your hardware/network.
// #define TOPIC "/buttons/cmd"
// #define stat/my_device/POWER  ON


byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 16, 70);
IPAddress server(192, 168, 16, 55);
EthernetClient ethClient;
PubSubClient client(ethClient);


class Light {
   public:
  boolean on = false;
  uint8_t outputNr;
  char *name;
  Button btn;
  
  Light(boolean _on, uint8_t _inputNr, uint8_t _outputNr, const char *_name): 
  on(_on), 
  btn(_inputNr), 
  outputNr(_outputNr), 
  name(_name) {
  }

  void toggle() {
    on=!on;
  }
  
  void send() {
    digitalWrite(outputNr, on);
    char strNr[10];
    char strOn[10];
    snprintf(strNr, 10, "%d",outputNr);
    snprintf(strOn, 10, "%d",on);
    client.publish(name, strOn);
  }
};


Light lights[] = {
 Light(false, CONTROLLINO_A0, CONTROLLINO_DO0, "lampe1"),
 Light(false, CONTROLLINO_A1, CONTROLLINO_DO1, "lampe2") 
};

void callback(char* topic, byte* payload, unsigned int length) {
  char *pch = strtok (topic, "/");
  if(pch!=NULL) {
    pch = strtok(NULL, "/");
    if(pch!=NULL) {
      Serial.println(pch);
      for(uint8_t i=0; i<(sizeof(lights)/sizeof(*lights)); i++) {
        Light &l=lights[i];
        if(strcmp(pch, l.name) == 0) {
          if(strcmp(payload, "ON")) {
            l.on=true;
            l.send();
          }
          else if(strcmp(payload, "OFF")) {
            l.on=false;
            l.send();   
          } 
        }
      }
      pch = strtok(NULL, "/");
    }
  }
}

long lastReconnectAttempt = 0;

boolean reconnect() {
  if (client.connect("iodub")) {
    client.subscribe("stat/+/power");
  }
  return client.connected();
}

void setup()
{
    Serial.begin(115200);
  Serial.println("-----------------------------------------");
  Serial.println("CONTROLLINO");
  Serial.println("-----------------------------------------");
  Serial.println("");

  
  for(int i=0; i<(sizeof(lights)/sizeof(*lights)); i++) {
    lights[i].btn.begin();
  }
  client.setServer(server, 1883);
  client.setCallback(callback);
    // Instantiate network from stored netowrk paramters in EEPROM.
  // If not in EEPROM then a random MAC will be generated and stored in EEPROM
  // in the form DE:AD:BE:EF:xx:xx where xx is a random number from 0 to 255.
  // If the netowrk is not configured in EEPROM, then DHCP will be used.
  NetEeprom.begin();
  lastReconnectAttempt = 0;
}



void mqtt() {
  if (!client.connected()) {
    digitalWrite(CONTROLLINO_DO7, LOW);
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    digitalWrite(CONTROLLINO_DO7, HIGH);
    client.loop();
  }
}

void loop() {
  mqtt();
  for(uint8_t i=0; i<(sizeof(lights)/sizeof(*lights)); i++) {
    //Light  *l=&lights[i];
    lights[i].btn.read();
    if (lights[i].btn.wasPressed()) {
      lights[i].toggle();
      lights[i].send();
  }
  }
}
