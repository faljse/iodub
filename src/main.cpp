#include <Controllino.h>
#include <EEPROM.h>
#include <SPI.h>
#include <string.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <NetEEPROM.h>
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
#include "config.h"
#include "analogmultibutton.h"

#include "dmx.h"


#define COUNT_OF(x) ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

EthernetUDP Udp;
boolean handlePacket();
void timer_init();
void printTasks();
void TaskMixer(void *pvParameters);
void TaskNetwork(void *pvParameters);
void TaskButtons(void *pvParameters);
void vMixerTimerCallback(TimerHandle_t xTimer);
void vPrintTimerCallback(TimerHandle_t xTimer);
uint8_t packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
enum UdpCmd: uint8_t {SetLight=1, RunAction=2};
TaskHandle_t taskNetworkHandle, taskButtonsHandle;
TimerHandle_t timerMixerHandler, timerPrintHandler;

void setup()
{
  buildConfig();

  dmx_init();
  Serial.begin(38400);
  Serial.println("--IODUB--");
  timerMixerHandler = xTimerCreate("Mixer", 2, pdTRUE,
                                   (void *)0,
                                   vMixerTimerCallback);
  timerPrintHandler = xTimerCreate("Print", 200, pdTRUE,
                                   (void *)0,
                                   vPrintTimerCallback);
  xTimerStart(timerMixerHandler,0);
  xTimerStart(timerPrintHandler,0);

  xTaskCreate(TaskNetwork, "Network", 
              384,         // Stack size
              NULL,
              0,                   // Priority
              &taskNetworkHandle); // Task handler
  xTaskCreate(TaskButtons, "Button", 
              384,         // Stack size
              NULL,
              0,                   // Priority
              &taskButtonsHandle); // Task handler
              

}

void vPrintTimerCallback(TimerHandle_t xTimer)
{
  printTasks();
  printDMX();
}

void vMixerTimerCallback(TimerHandle_t xTimer)
{
  dmx_fade();
}

void TaskNetwork(void *pvParameters)
{
  byte mac[6] = { 0xCA, 0xFE, 0xBA, 0xBE, 0x00, 0x00 };
  byte ip[4] = { 192, 168, 16, 111 };
  byte dns[4] = { 8, 8, 8, 8 };
  byte gw[4] = { 192, 168, 16, 1 };
  byte subnet[4] = { 255, 255, 255, 0 };
  NetEeprom.writeManualConfig(mac, ip, dns, gw, subnet);
  NetEeprom.begin();
  Udp.begin(1717);
  for (;;)
  {
    if(!handlePacket()){
       vTaskDelay(1); // if there was no packet, there is also none queued.. sleep for 1 tick
       // avg first reply takes tick/2
    }
  }
}

void TaskButtons(void *pvParameters)
{

  for(;;){
      for(uint8_t i=0; i<COUNT_OF(buttons); i++) {
      buttons[i].update();
    }
  }
}
char ptrTaskList[200];
void tasks(char *pcWriteBuffer);
void printTasks()
{
  tasks(ptrTaskList);
  Serial.println(F("--"));
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
        if(ulStatsAsPercentage<1)
          ulStatsAsPercentage=1;
        if(ulStatsAsPercentage>99)
          ulStatsAsPercentage=99;
        char cStatus;
        switch( pxTaskStatusArray[ x ].eCurrentState )
        {
            case eRunning:      cStatus = 'X';
                                break;
            case eReady:        cStatus = 'R';
                                break;
            case eBlocked:      cStatus = 'B';
                                break;
            case eSuspended:    cStatus = 'S';
                                break;
            case eDeleted:      cStatus = 'D';
                                break;
            case eInvalid:      /* Fall through. */
            default:            /* Should not get here, but it is included
                                to prevent static checking errors. */
                                cStatus = ( char ) 0x00;
                                break;
        }
        sprintf( pcWriteBuffer, "%u:%8s %05lu %02lu%% %c %02up %03ub\r\n",
                  (unsigned int) pxTaskStatusArray[x].xTaskNumber, 
                  pxTaskStatusArray[x].pcTaskName,
                  pxTaskStatusArray[x].ulRunTimeCounter,
                  ulStatsAsPercentage, 
                  cStatus, 
                  (unsigned int) pxTaskStatusArray[x].uxCurrentPriority, 
                  pxTaskStatusArray[x].usStackHighWaterMark);
        pcWriteBuffer += strlen((char *)pcWriteBuffer);

      }
    }

    /* The array is no longer needed, free the memory it consumes. */
    vPortFree(pxTaskStatusArray);
  }
}

boolean handlePacket()
{
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    IPAddress remote = Udp.remoteIP();
    uint16_t port = Udp.remotePort();
    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    switch (packetBuffer[0])
    {
      case SetLight:
        break;
      case RunAction:
        uint8_t id=packetBuffer[1];
        for (uint8_t i = 0; i < COUNT_OF(asg); i++)
        {
          if(asg->id==id) {
            asg->next();
          }
          // Action *a=actions[i];
          // if(id==a->actionset_id) {
          //  lights[a->light_idx]->cmd(a);
          //}
        }
        Udp.beginPacket(remote, port);
        Udp.write("OK");
        Udp.endPacket();
        break;
      default:
          Udp.beginPacket(remote, port);
          Udp.write("NOK");
          Udp.endPacket();
          break;
      }
    }
  else {
    return false;
  }
}