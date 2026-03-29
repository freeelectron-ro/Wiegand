#include <Arduino.h>
#include "wiegand_tx.h"

#define JUMPER_T0    6
#define JUMPER_T1    7
#define JUMPER_W     8
#define CONTACT      9

#define DATA_W26    0x00123456
#define DATA_W34    0x12345678

#define DEBOUNCE_TIME  100

void setup(void)
{
	pinMode(LED_BUILTIN, OUTPUT);
	
	pinMode(JUMPER_T0, INPUT_PULLUP);
	pinMode(JUMPER_T1, INPUT_PULLUP);
	pinMode(JUMPER_W,  INPUT_PULLUP);
	pinMode(CONTACT,   INPUT_PULLUP);
	
	WTX_Init(2, 3);
}

bool check_contact(void)
{
	bool retVal = false;
	static bool prev_state = false;
	bool actual_state = (digitalRead(CONTACT))? false : true; // true means pressed
	static unsigned long t0 = 0;
	unsigned long t1 = millis();
	
	if(actual_state != prev_state)
	{
		if((t1 - t0) > DEBOUNCE_TIME)
		{
			prev_state = actual_state;
			retVal = actual_state;
		}
	}
	else
		t0 = t1;
	return retVal;
}

void apply_delay(void)
{
	bool t0 = digitalRead(JUMPER_T0) ? false : true;  // true means jumper set
	bool t1 = digitalRead(JUMPER_T1) ? false : true;
	switch(t1 * 2 + t0)
	{
		case 1:   delay(1666); break;
		case 2:   delay(2333); break;
		case 3:   delay(3000); break;
		default:  delay(1000); break;
	}
}

void send(void)
{
	digitalWrite(LED_BUILTIN, HIGH);
	if(digitalRead(JUMPER_W))
		WTX_Send26(DATA_W26);
	else
		WTX_Send34(DATA_W34);
	digitalWrite(LED_BUILTIN, LOW);
}


void loop(void)
{
	if(check_contact())
	{
		apply_delay();
		send();
	}
}
