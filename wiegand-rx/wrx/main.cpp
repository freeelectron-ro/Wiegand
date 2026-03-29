#include <Arduino.h>
#include "wiegand_rx.h"

void setup(void)
{
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);
	WRX_Init(2, 3);
}

void loop(void)
{
	if(WRX_IsAvailable())
	{
		digitalWrite(LED_BUILTIN, HIGH);

		Serial.print("Wiegand HEX = ");
		Serial.print(WRX_GetCode(), HEX);

		Serial.print(", Type ");
		switch(WRX_GetType())
		{
			case WIEGAND_TYPE_26: Serial.print("Wiegand-26"); break;
			case WIEGAND_TYPE_34: Serial.print("Wiegand-34"); break;
			default:              Serial.print("Unknown"); break;
		}
		
		if(WRX_IsValid())
    		Serial.println(", Valid Parity");
		else
			Serial.println(", Invalid Parity");

		digitalWrite(LED_BUILTIN, LOW);
	}
}
