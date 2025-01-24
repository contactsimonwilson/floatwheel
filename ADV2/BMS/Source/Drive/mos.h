#ifndef __MOS_H
#define __MOS_H

#include "n32l40x.h"

#define DSG_ON  	GPIOB->PBSC =  GPIO_PIN_0;		//�ŵ�MOS��
#define DSG_OFF		GPIOB->PBC  =  GPIO_PIN_0;		//�ŵ�MOS�ر�

#define CHG_ON		GPIOB->PBSC =  GPIO_PIN_1;		//���MOS��
#define CHG_OFF		GPIOB->PBC  =  GPIO_PIN_1;		//���MOS�ر�

#define PDSG_ON		GPIOB->PBSC =  GPIO_PIN_3;		//Ԥ��MOS��
#define PDSG_OFF	GPIOB->PBC  =  GPIO_PIN_3;		//Ԥ��MOS�ر�

#define PCHG_ON		GPIOA->PBSC =  GPIO_PIN_15;		//Ԥ��MOS��
#define PCHG_OFF	GPIOA->PBC  =  GPIO_PIN_15;		//Ԥ��MOS�ر�

#define CHARG_ON	GPIOA->PBSC =  GPIO_PIN_7;		//�������
#define CHARG_OFF	GPIOA->PBC  =  GPIO_PIN_7;		//������ر�

void MOS_Init(void);

#endif

