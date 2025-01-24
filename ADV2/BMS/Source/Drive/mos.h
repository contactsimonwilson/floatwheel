#ifndef __MOS_H
#define __MOS_H

#include "n32l40x.h"

#define DSG_ON  	GPIOB->PBSC =  GPIO_PIN_0;		//放电MOS打开
#define DSG_OFF		GPIOB->PBC  =  GPIO_PIN_0;		//放电MOS关闭

#define CHG_ON		GPIOB->PBSC =  GPIO_PIN_1;		//充电MOS打开
#define CHG_OFF		GPIOB->PBC  =  GPIO_PIN_1;		//充电MOS关闭

#define PDSG_ON		GPIOB->PBSC =  GPIO_PIN_3;		//预放MOS打开
#define PDSG_OFF	GPIOB->PBC  =  GPIO_PIN_3;		//预放MOS关闭

#define PCHG_ON		GPIOA->PBSC =  GPIO_PIN_15;		//预充MOS打开
#define PCHG_OFF	GPIOA->PBC  =  GPIO_PIN_15;		//预充MOS关闭

#define CHARG_ON	GPIOA->PBSC =  GPIO_PIN_7;		//充电器打开
#define CHARG_OFF	GPIOA->PBC  =  GPIO_PIN_7;		//充电器关闭

void MOS_Init(void);

#endif

