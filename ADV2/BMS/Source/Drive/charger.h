#ifndef __CHARGER_H
#define __CHARGER_H

#include "n32l40x.h"

#define CHARGER		((GPIOA->PID>>8)&1)
//#define CHARGER_H	GPIOA->PBSC =  GPIO_PIN_4;		//�ߵ�ƽ
//#define CHARGER_L	GPIOA->PBC  =  GPIO_PIN_4;		//�͵�ƽ

void Charger_Init(void);
	
#endif


