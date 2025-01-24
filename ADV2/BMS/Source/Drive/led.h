#ifndef __LED_H
#define __LED_H

#include "n32l40x.h"

#define LED_ON		GPIOA->PBC  =  GPIO_PIN_3;		//�͵�ƽ
#define LED_OFF		GPIOA->PBSC =  GPIO_PIN_3;		//�ߵ�ƽ
#define LED_FLIP 	GPIOA->POD ^=  GPIO_PIN_3;

void LED_Init(void);

#endif

