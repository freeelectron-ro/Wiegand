#include <Arduino.h>
#include "wiegand_tx.h"

void setup(void)
{
	Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);
	WTX_Init(2, 3);
}

void send(uint32_t data)
{
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.print("Wiegand-26 HEX = ");
	Serial.println(data & 0x00FFFFFF, HEX);
	WTX_Send26(data);
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
	digitalWrite(LED_BUILTIN, HIGH);
	Serial.print("Wiegand-34 HEX = ");
	Serial.println(data, HEX);
	WTX_Send34(data);
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
}

void loop(void)
{
	send(0x00000000);
	send(0xFFFFFFFF);
	send(0xAAAAAAAA);
	send(0x12345678);
	send(0x00123456);
}
