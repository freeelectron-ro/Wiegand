#include <Arduino.h>
#include "wiegand_tx.h"

static int pin_W0, pin_W1;

// outputs ONE Wiegand bit
static void send_bit(bool bit)
{
	int pin = (bit)? pin_W1 : pin_W0;
	digitalWrite(pin, 0);
	delayMicroseconds(100);
	digitalWrite(pin, 1);
	delayMicroseconds(400);
}

void WTX_Init(int W0, int W1)
{
	pin_W0 = W0;
	pin_W1 = W1;
	pinMode(W0, OUTPUT);  
  	pinMode(W1, OUTPUT);
  	digitalWrite(W0, 1); // set line to IDLE state
  	digitalWrite(W1, 1);
}

void WTX_Send26(uint32_t data)
{
	uint32_t tmp = data, mask;
	uint8_t n;
	bool p_even = 0;
  	bool p_odd = 1;

	// compute parity on trailing group of bits 
	for(n = 0; n < 12; n++)
	{
		p_odd ^= (bool)(tmp & 1);
		tmp >>= 1;
	}
  	// compute parity on heading group of bits
	for (n = 12; n < 24; n++)
	{
		p_even ^= (bool)(tmp & 1);
		tmp >>= 1;
	}

	send_bit(p_even);
  	for (mask = (1UL << 23); mask != 0; mask >>= 1)
  	{
		bool b = (data & mask)? 1 : 0;
    	send_bit(b);
  	}
  	send_bit(p_odd);
}

void WTX_Send34(uint32_t data)
{
	uint32_t tmp = data, mask;
	uint8_t n;
	bool p_even = 0;
  	bool p_odd = 1;

	// compute parity on trailing group of bits 
	for(n = 0; n < 16; n++)
	{
		p_odd ^= (bool)(tmp & 1);
		tmp >>= 1;
	}
  	// compute parity on heading group of bits
	for (n = 16; n < 32; n++)
	{
		p_even ^= (bool)(tmp & 1);
		tmp >>= 1;
	}

	send_bit(p_even);
  	for (mask = (1UL << 31); mask != 0; mask >>= 1)
  	{
		bool b = (data & mask)? 1 : 0;
    	send_bit(b);
  	}
  	send_bit(p_odd);
}
