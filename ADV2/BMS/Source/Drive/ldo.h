#ifndef __LDO_H
#define __LDO_H

#include "n32l40x.h"

#define LDO_ON		GPIOB->PBSC = GPIO_PIN_4;	//�ߵ�ƽ
#define LDO_OFF		GPIOB->PBC  = GPIO_PIN_4;	//�͵�ƽ

void LDO_Init(void);

#endif


