#include <Controllino.h>
#include <JC_Button.h>
#include <EEPROM.h>
#include <SPI.h>
#include "ModbusRtu.h"
#include "light.h"
#include "room.h"

#include <string.h>

// For any Modbus slave devices are reserved addresses in the range from 1 to 247.
// Important note only address 0 is reserved for a Modbus master device!
#define MasterModbusAdd  0
#define SlaveModbusAdd  1


// This MACRO defines number of the comport that is used for RS 485 interface.
// For MAXI and MEGA RS485 is reserved UART Serial3.
#define RS485Serial     3
// The object ControllinoModbuSlave of the class Modbus is initialized with three parameters.
// The first parametr specifies the address of the Modbus slave device.
// The second parameter specifies type of the interface used for communication between devices - in this sketch is used RS485.
// The third parameter can be any number. During the initialization of the object this parameter has no effect.
Modbus ControllinoModbusMaster(MasterModbusAdd, RS485Serial, 0);

// This is an structe which contains a query to an slave device
modbus_t ModbusQuery;
uint16_t ModbusSlaveRegisters[8];


uint8_t myState; // machine state
uint8_t currentQuery; // pointer to message query

unsigned long WaitingTime;




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

void setup()
{
  Serial.begin(19200);
  Serial.println("-----------------------------------------");
  Serial.println("CONTROLLINO Modbus RTU Master Test Sketch");
  Serial.println("-----------------------------------------");
  Serial.println("");
    // ModbusQuery 0: read registers
  ModbusQuery.u8id = SlaveModbusAdd; // slave address
  ModbusQuery.u8fct = 3; // function code (this one is registers read)
  ModbusQuery.u16RegAdd = 0; // start address in slave
  ModbusQuery.u16CoilsNo = 4; // number of elements (coils or registers) to read
  ModbusQuery.au16reg = ModbusSlaveRegisters; // pointer to a memory array in the CONTROLLINO

  ControllinoModbusMaster.begin( 19200 ); // baud-rate at 19200
  ControllinoModbusMaster.setTimeOut( 1000 ); // if there is no answer in 5000 ms, roll over
  
  WaitingTime = millis() + 1000;
  myState = 0;
  currentQuery = 0; 

  for(int i=0; i<(sizeof(lights)/sizeof(*lights)); i++) {
    lights[i].inputNr.begin();
  }
    // Instantiate network from stored netowrk paramters in EEPROM.
  // If not in EEPROM then a random MAC will be generated and stored in EEPROM
  // in the form DE:AD:BE:EF:xx:xx where xx is a random number from 0 to 255.
  // If the netowrk is not configured in EEPROM, then DHCP will be used.
}




void loop() {
    ControllinoModbusMaster.query( ModbusQuery ); // send query (only once)
    ControllinoModbusMaster.poll(); // check incoming messages
    if (ControllinoModbusMaster.getState() == COM_IDLE) 
      {
        // response from the slave was received
        myState = 0;
        WaitingTime = millis() + 1000; 
        // registers read was proceed
        Serial.println("---------- READ RESPONSE RECEIVED ----");
        Serial.print("Slave ");
        Serial.print(SlaveModbusAdd, DEC); 
        Serial.print(" ADC0: 0x");
        Serial.print(ModbusSlaveRegisters[0], HEX);
        Serial.print(" , Digital0: ");
        Serial.print(ModbusSlaveRegisters[1], BIN);
        Serial.print(" , ModbusCounterIn: ");
        Serial.print(ModbusSlaveRegisters[2], DEC);
        Serial.print(" , ModbusCounterOut: ");
        Serial.println(ModbusSlaveRegisters[3], DEC);
        Serial.println("-------------------------------------");
        Serial.println("");
      }
}
