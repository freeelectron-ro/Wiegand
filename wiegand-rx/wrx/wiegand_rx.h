#ifndef WIEGAND_RX_H
#define WIEGAND_RX_H


#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus 
extern "C" {
#endif


typedef enum
{
	WIEGAND_TYPE_UNKNOWN,
	WIEGAND_TYPE_26,
	WIEGAND_TYPE_34
} wgType_t;

void     WRX_Init(int, int);
bool     WRX_IsAvailable(void);
bool     WRX_IsValid(void);
uint32_t WRX_GetCode(void);
wgType_t WRX_GetType(void);

#ifdef __cplusplus
}
#endif

#endif /* WIEGAND_RX_H */

