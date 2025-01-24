#ifndef __POWER_H
#define __POWER_H

#include "hk32f030m.h"

#define  PWR_ON     	GPIOA->BSRR = GPIO_Pin_2;
#define  PWR_OFF    	GPIOA->BRR  = GPIO_Pin_2;

//#define  CHARGE_ON		GPIOC->BSRR = GPIO_Pin_5;
//#define  CHARGE_OFF		GPIOC->BRR  = GPIO_Pin_5;

void Power_Init(void);

#endif


