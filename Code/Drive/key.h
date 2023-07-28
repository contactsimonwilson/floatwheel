#ifndef __KEY_H
#define __KEY_H

#include "hk32f030m.h"
#include "test.h"
#include "buzzer.h"

#define KEY1 ((GPIOC->IDR>>3)&1)

extern uint8_t KEY1_State;

void KEY_Init(void);
void KEY1_Scan(void);


#endif


