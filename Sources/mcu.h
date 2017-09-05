#ifndef __MCU_H__
#define __MCU_H__
#include "FreeRTOS.h"

void MCUInit(uint8_t fbus);
void MCUReset(void);

#endif
