#ifndef __LDO_H
#define __LDO_H

#include "n32l40x.h"

#define LDO_ON		GPIOB->PBSC = GPIO_PIN_4;	//高电平
#define LDO_OFF		GPIOB->PBC  = GPIO_PIN_4;	//低电平

void LDO_Init(void);

#endif


