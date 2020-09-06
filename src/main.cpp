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
#include <utility/w5100.h>
extern "C" void vConfigureTimerForRunTimeStats(void)
{
}

extern "C" unsigned long vGetTimerForRunTimeStats(void)
{
  return micros();
}

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <timers.h>

#define TLight 1
#define TDim 2
#define COUNT_OF(x) ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

EthernetUDP Udp;
void handlePacket();
void timer_init();
void printTasks();
void TaskMixer(void *pvParameters);
void TaskNetwork(void *pvParameters);
void vMixerTimerCallback(TimerHandle_t xTimer);

Room room[] = {
    Room(1, "Salon"),
    Room(2, "Miranda"),
    Room(3, "Kueche"),
    Room(4, "BadUnten"),
    Room(5, "BadOben"),
};

Light lights[] = {
    Light(1, 1, false, CONTROLLINO_A0, CONTROLLINO_D11, "Lampe"),
    Light(2, 2, false, CONTROLLINO_A1, CONTROLLINO_D11, "Lampe"),
    Light(3, 2, false, CONTROLLINO_A1, CONTROLLINO_D11, "Lampe"),
    Light(4, 2, false, CONTROLLINO_A1, CONTROLLINO_D11, "Lampe")};

Dimmer dimmers[] = {
    Dimmer(1, 1, 1, 2, "Leds am Tisch1"),
    Dimmer(2, 1, 3, 4, "Leds am Tisch2")

};

Terminal terminals[] = {
    Terminal(1, 1, "SalonTerminal"),
};
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

TaskHandle_t taskNetworkHandle;
TimerHandle_t timerMixerHandler;

void setup()
{
  for (int i = 0; i < COUNT_OF(lights); i++)
  {
    lights[i].inputNr.begin();
  }
  dmx_init();
  Serial.begin(19200);
  Serial.println("--IODUB--");
  NetEeprom.begin();
  Udp.begin(1717);
  timerMixerHandler = xTimerCreate("Mixer", 2, pdTRUE,
                                   (void *)0,
                                   vMixerTimerCallback);
  xTimerStart(timerMixerHandler,0);
  xTaskCreate(TaskNetwork, "Network", 
              128,         // Stack size
              NULL,
              0,                   // Priority
              &taskNetworkHandle); // Task handler
}
void vMixerTimerCallback(TimerHandle_t xTimer)
{
  for (uint8_t i = 0; i != DMX_CHANNELS; i++)
  {
    int16_t diff = dmx_set[i] - dmx_cur[i];
    dmx_cur[i] = dmx_cur[i] + diff;
  }
}

void TaskNetwork(void *pvParameters)
{
  for (;;)
  {
    handlePacket();
  }
}

void loop()
{
  vTaskDelay(200);
  printTasks();
}

char ptrTaskList[250];
void tasks(char *pcWriteBuffer);

void printTasks()
{
  tasks(ptrTaskList);
  Serial.println(F("**********************************"));
  Serial.print(ptrTaskList);
}

void tasks(char *pcWriteBuffer)
{
  TaskStatus_t *pxTaskStatusArray;
  volatile UBaseType_t uxArraySize, x;
  uint32_t ulTotalRunTime, ulStatsAsPercentage;

  /* Make sure the write buffer does not contain a string. */
  *pcWriteBuffer = 0x00;

  /* Take a snapshot of the number of tasks in case it changes while this
   function is executing. */
  uxArraySize = uxTaskGetNumberOfTasks();

  /* Allocate a TaskStatus_t structure for each task.  An array could be
   allocated statically at compile time. */
  pxTaskStatusArray = (TaskStatus_t *)pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

  if (pxTaskStatusArray != NULL)
  {

    /* Generate raw status information about each task. */
    uxArraySize = uxTaskGetSystemState(pxTaskStatusArray,
                                       uxArraySize,
                                       &ulTotalRunTime);
    /* For percentage calculations. */
    ulTotalRunTime /= 100UL;
    /* Avoid divide by zero errors. */
    if (ulTotalRunTime > 0)
    {
      /* For each populated position in the pxTaskStatusArray array,
         format the raw data as human readable ASCII data. */
      for (x = 0; x < uxArraySize; x++)
      {
        /* What percentage of the total run time has the task used?
            This will always be rounded down to the nearest integer.
            ulTotalRunTimeDiv100 has already been divided by 100. */
        ulStatsAsPercentage =
            pxTaskStatusArray[x].ulRunTimeCounter / ulTotalRunTime;

        if (ulStatsAsPercentage > 0UL)
        {
          sprintf(pcWriteBuffer, "%s\t\t%lu\t\t%lu%%\r\n",
                  pxTaskStatusArray[x].pcTaskName,
                  pxTaskStatusArray[x].ulRunTimeCounter,
                  ulStatsAsPercentage);
        }
        else
        {
          /* If the percentage is zero here then the task has
               consumed less than 1% of the total run time. */
          sprintf(pcWriteBuffer, "%s\t\t%lu\t\t<1%%\r\n",
                  pxTaskStatusArray[x].pcTaskName,
                  pxTaskStatusArray[x].ulRunTimeCounter);
        }

        pcWriteBuffer += strlen((char *)pcWriteBuffer);
      }
    }

    /* The array is no longer needed, free the memory it consumes. */
    vPortFree(pxTaskStatusArray);
  }
}

void handlePacket()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    IPAddress remote = Udp.remoteIP();
    uint16_t port = Udp.remotePort();
    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    switch (packetBuffer[1])
    {
    case TLight:
      break;
    case TDim:
      for (uint8_t i = 0; i != COUNT_OF(dimmers); i++)
      {
        Dimmer &d = dimmers[i];
        uint8_t id = packetBuffer[2];
        if (d.nr == id)
        {
          uint8_t chanNr = packetBuffer[3];
          uint8_t brightVal = packetBuffer[4];
          if (chanNr == 0)
            d.valWW = brightVal;
          if (chanNr == 1)
            d.valCW = brightVal;
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
