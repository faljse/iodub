#include <Controllino.h>
#include <EEPROM.h>
#include <SPI.h>
#include <string.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <NetEEPROM.h>
#include <utility/w5100.h>
#include <mqtt.h>
extern "C" void vConfigureTimerForRunTimeStats(void)
{
}

extern "C" int vGetTimerForRunTimeStats(void)
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

void timer_init();
void printTasks();
void printAnalog();
void TaskMixer(void *pvParameters);
void TaskNetwork(void *pvParameters);
void vMixerTimerCallback(TimerHandle_t xTimer);
void vButtonTimerCallback(TimerHandle_t xTimer);
void vPrintTimerCallback(TimerHandle_t xTimer);

TaskHandle_t taskNetworkHandle, taskButtonsHandle;
TimerHandle_t timerMixerHandler, timerPrintHandler, timerButtonHandler;

EthernetClient *ethClient;
PubSubClient *psclient;

void setup()
{
  buildConfig();

  dmx_init();
  Serial.begin(38400);
  Serial.println("--IODUB--");
  timerMixerHandler = xTimerCreate("Mixer", 2, pdTRUE,
                                   (void *)0,
                                   vMixerTimerCallback);
  timerButtonHandler = xTimerCreate("Button", 3, pdTRUE,
                                   (void *)0,
                                   vButtonTimerCallback);
  timerPrintHandler = xTimerCreate("Print", 1000, pdTRUE,
                                    (void *)0,
                                    vPrintTimerCallback);
  xTimerStart(timerMixerHandler,0);
  xTimerStart(timerButtonHandler,0);
  xTimerStart(timerPrintHandler,0);


  xTaskCreate(TaskNetwork, "Network", 
              384,         // Stack size
              NULL,
              0,                   // Priority
              &taskNetworkHandle); // Task handler

                for(uint8_t i=CONTROLLINO_A0;i!=CONTROLLINO_A15;i++){
                  pinMode(i, INPUT);
                }
                for(uint8_t i=CONTROLLINO_R0;i!=CONTROLLINO_R15;i++){
                  pinMode(i, OUTPUT);
                }
  bitClear(ADCSRA,ADPS0); 
  bitSet(ADCSRA,ADPS1); 
  bitClear(ADCSRA,ADPS2);
}

void vPrintTimerCallback(TimerHandle_t xTimer)
{
  printTasks();
  // printDMX();
  printAnalog();
}

void vButtonTimerCallback(TimerHandle_t xTimer)
{
  
  for(uint8_t i=0; i<COUNT_OF(abuttons); i++) {
    abuttons[i].update();
  }
}

void vMixerTimerCallback(TimerHandle_t xTimer)
{
  dmx_fade();
}

void TaskNetwork(void *pvParameters)
{
  byte mac[6] = { 0xCA, 0xFE, 0xBA, 0xBE, 0x00, 0x00 };
  byte ip[4] = { 192, 168, 0, 2 };
  byte dns[4] = { 8, 8, 8, 8 };
  byte gw[4] = { 192, 168, 0, 1 };
  byte subnet[4] = { 255, 255, 255, 0 };
  NetEeprom.writeManualConfig(mac, ip, dns, gw, subnet);
  NetEeprom.begin();
  ethClient = new EthernetClient();
  psclient = new PubSubClient(*ethClient);
  IPAddress server(192,168,0,1); 


  psclient->setServer(server, 1883);
  for (;;)
  {
      if (!psclient->connected()) {
        reconnectMQTT(psclient);
        //psclient->setCallback(callbackMQTT);
        // psclient->subscribe("home/light/#");
      }
      else {
        psclient->loop();
        if(!ethClient->available()) {
          vTaskDelay(1); // sleep for 1 tick to avoid busy loop
        }
      }
  }
}

char ptrTaskList[400];
void tasks(char *pcWriteBuffer);
void printTasks()
{
  tasks(ptrTaskList);
  Serial.print(ptrTaskList);
}
void printAnalog()
{
  Serial.print("A: ");
  for(uint8_t i=CONTROLLINO_A0;i!=CONTROLLINO_A15;i++){
    Serial.print(i);
    Serial.print(":");
    Serial.print(analogRead(i));
    Serial.print(" ");
  }
  Serial.println();
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
                  pxTaskStatusArray[x].uxStackHighWaterMark);
        pcWriteBuffer += strlen((char *)pcWriteBuffer);

      }
    }

    /* The array is no longer needed, free the memory it consumes. */
    vPortFree(pxTaskStatusArray);
  }
}
