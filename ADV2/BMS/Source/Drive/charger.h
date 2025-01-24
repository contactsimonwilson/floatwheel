#ifndef __CHARGER_H
#define __CHARGER_H

#include "n32l40x.h"

#define CHARGER		((GPIOA->PID>>8)&1)
//#define CHARGER_H	GPIOA->PBSC =  GPIO_PIN_4;		//高电平
//#define CHARGER_L	GPIOA->PBC  =  GPIO_PIN_4;		//低电平

void Charger_Init(void);
	
#endif


