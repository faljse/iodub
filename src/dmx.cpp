#include "dmx.h"

volatile unsigned char dmx_cur[DMX_CHANNELS];
volatile unsigned char dmx_set[DMX_CHANNELS];

void printDMX()
{
  Serial.print("DMX: ");
  for(int i=0;i<DMX_CHANNELS;i++) {
	  Serial.print(dmx_cur[i]);	  
	  Serial.print(",");
  }
  Serial.println();
}

void dmx_fade() 
{
  for (uint8_t i = 0; i != DMX_CHANNELS; i++)
  {
    int16_t diff = dmx_set[i] - dmx_cur[i];
    dmx_cur[i] = dmx_cur[i] + diff;
  }
}
void dmx_setch(uint8_t channel, uint8_t value)
{
      dmx_set[channel] = value;
}

void dmx_init() {
	UBRR3   = (F_CPU / (DMX_BAUD * 16L) - 1);
	UCSR3B|=(1<<TXEN3)|(1<<TXCIE3); // TXEN0 Transmitter enable / TXCIE0 TX complete interrupt enable 
	UCSR3C|=(1<<USBS3); //USBS0 2 Stop bits	
    pinMode(CONTROLLINO_RS485_TX, OUTPUT);
    pinMode(CONTROLLINO_RS485_RX, INPUT);
    pinMode(CONTROLLINO_RS485_nRE, OUTPUT);
    pinMode(CONTROLLINO_RS485_DE, OUTPUT);
    digitalWrite (CONTROLLINO_RS485_nRE, HIGH);
    digitalWrite (CONTROLLINO_RS485_DE, HIGH);
	UDR3 = 0;//Start DMX
}

ISR (USART3_TX_vect)
{
	static unsigned int  dmx_channel_tx_count = 0;
	static unsigned char dmx_tx_state = 0;
	switch (dmx_tx_state)
	{
		case (0):
			UBRR3   = (F_CPU / (DMX_BAUD_BREAK * 16L) - 1);
			UDR3 = 0; //RESET Frame
			dmx_tx_state = 1;
			break;
 
		case (1):
			UBRR3   = (F_CPU / (DMX_BAUD * 16L) - 1);
			UDR3 = 0; //Start Byte
			dmx_tx_state = 2;
			break;
 
		case (2):
			_delay_us(10);
			//Ausgabe des Zeichens
			UDR3 =  dmx_cur[dmx_channel_tx_count];
			dmx_channel_tx_count++;
 
			if(dmx_channel_tx_count == DMX_CHANNELS)
			{
				dmx_channel_tx_count = 0;
				dmx_tx_state = 0;
			}
			break;
	}
}
