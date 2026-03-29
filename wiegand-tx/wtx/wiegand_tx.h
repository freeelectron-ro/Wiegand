#ifndef WIEGAND_TX_H
#define WIEGAND_TX_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus 
extern "C" {
#endif


void WTX_Init(int, int);
void WTX_Send26(uint32_t);
void WTX_Send34(uint32_t);

#ifdef __cplusplus
}
#endif

#endif /* WIEGAND_TX_H */
