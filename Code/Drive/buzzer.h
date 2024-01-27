#ifndef __BUZZER_H
#define __BUZZER_H

#include "hk32f030m.h"

#define  BUZZER_ON     	GPIOA->BSRR = GPIO_Pin_3;
#define  BUZZER_OFF    	GPIOA->BRR  = GPIO_Pin_3;

void Buzzer_Init(void);
void Buzzer_Ring(uint16_t ring_time);
void Buzzer_Scan(void);

#endif

