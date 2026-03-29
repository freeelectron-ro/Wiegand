#include <Arduino.h>
#include "wiegand_rx.h"



static int pinW0, pinW1;

/* data to be passed to the app */
static uint32_t code;
static bool     p1, p2;
static wgType_t type;

/* data used for temporary store during bits load */
static volatile uint64_t dataLoad;
static volatile unsigned long bitTimeStamp;
static volatile uint8_t bitCount;

static bool BitParityCompute(uint64_t data, uint64_t mask, bool init)
{
	bool parity = init;
	uint64_t m;
	for(m = (1ULL<<63); m != 0 ; m >>= 1)
	{
		if(m & mask & data)
			parity ^= 1;
	}
	return parity;
}

static void BitProcess(bool bit)
{
	bitCount++;
	bitTimeStamp = millis();
	dataLoad <<= 1;
	if(bit) dataLoad |= 1;
}

static void ReadW0(void)
{
	BitProcess(false);
}

static void ReadW1(void)
{
	BitProcess(true);
}


void WRX_Init(int w0, int w1)
{
	bitTimeStamp = 0;
	bitCount = 0;
	code = 0;
	dataLoad = 0;
	
	pinW0 = w0;
	pinW1 = w1;
	
	pinMode(w0, INPUT);
	pinMode(w1, INPUT);	
	
	noInterrupts();
	
	attachInterrupt(digitalPinToInterrupt(w1), ReadW1, FALLING);  // Hardware interrupt - falling transition
	attachInterrupt(digitalPinToInterrupt(w0), ReadW0, FALLING);  // Hardware interrupt - falling transition
	
	interrupts();
}

bool     WRX_IsValid(void)
{
	return (p1 || p2)? false : true;
}

uint32_t WRX_GetCode(void)
{
	return code;
}

wgType_t WRX_GetType(void)
{
	return type;
}

bool     WRX_IsAvailable(void)
{
	bool retVal = false;
	unsigned long timeStamp = millis();
	noInterrupts();
	
	if(  (timeStamp - bitTimeStamp) > 10)
	{
		if(bitCount == 26)
		{
			code = (uint32_t)((dataLoad >> 1) & 0x00FFFFFF);
			p1 = BitParityCompute(dataLoad, 0x0000000000001FFFULL, 1);
			p2 = BitParityCompute(dataLoad, 0x0000000003FFE000ULL, 0);
			type = WIEGAND_TYPE_26;
			retVal = true;
		}
		else if(bitCount == 34)
		{
			code = (uint32_t)(dataLoad >> 1);
			p1 = BitParityCompute(dataLoad, 0x000000000001FFFFULL, 1);
			p2 = BitParityCompute(dataLoad, 0x00000003FFFE0000ULL, 0);
			type = WIEGAND_TYPE_34;
			retVal = true;
		}

		bitTimeStamp = timeStamp;
		bitCount = 0;
		dataLoad = 0;
	}

	interrupts();
	return retVal;
}

