#ifndef __KEY_H
#define __KEY_H

#include "n32l40x.h"

#define KEY1 ((GPIOA->PID>>0)&1)

extern uint8_t KEY1_State;

void KEY_Init(void);
void KEY1_Scan(void);

#endif


