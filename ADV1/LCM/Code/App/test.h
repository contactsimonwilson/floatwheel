#ifndef __TEST_H
#define __TEST_H

#include "hk32f030m.h"
#include "adc.h"
#include "power.h"
#include "led.h"
#include "vesc_uasrt.h"
#include "buzzer.h"

extern uint8_t  Test_Step;
extern uint16_t Test_Counter;

void Test_ADC(void);
void Test_Task(void);
void Test_USART(void);

#endif


