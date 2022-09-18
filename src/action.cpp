#include <Controllino.h>
#include "dmx.h"
#include "mqtt.h"
#include "config.h"
#include "relay.h"
#include "dimmer.h"
#include "action.h"

void sendAction(uint8_t aidx){
  sendAction(aidx,255);
}

void sendAction(uint8_t aidx, uint8_t setpos){
        if(aidx>COUNT_OF(actionstate))
          return;
        uint8_t pos=actionstate[aidx]+1;
        if(pgm_read_byte(&actions[aidx][pos][0])==0) {//terminating zero - reset to pos 0
          pos=0;
        }
        if(setpos!=255)
          pos=setpos;
        for(uint8_t i=0;i<10;i++) {
          uint8_t id=pgm_read_byte(&actions[aidx][pos][i*2]);  
          uint8_t val=pgm_read_byte(&actions[aidx][pos][i*2+1]);
          if(id==0) break;
          if(id<100) sendRelay(id, val);
          if(id<200) sendDimmer(id, val);
          else sendAction(id-200, val);
          
        }
        actionstate[aidx]=pos;

}