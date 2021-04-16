#ifndef DMX_H
#define DMX_H

#include <Controllino.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DMX_BAUD 250000
#define DMX_BAUD_BREAK 80000
#define DMX_CHANNELS 32



// https://www.ulrichradig.de/home/index.php/avr/atmega8-experimentierboard/avr---dmx
ISR (USART3_TX_vect);
void printDMX();
void dmx_init(); 
void dmx_fade();
void dmx_setch(uint8_t channel, uint8_t value);

#endif