#include "io_ws2812.h"

void IO_WS2812_Init_In(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	
	GPIO_StructInit(&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIOD->BSRR = GPIO_Pin_4;
}

void IO_WS2812_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIOD->BSRR = GPIO_Pin_4;
}

/*		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4; 750ns
*/

/*
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4;
		GPIOD->BSRR = GPIO_Pin_4; 250ns
*/

/*
	void delay(uint16_t i)
	{
		while(i--);
	}
	i=250 120us
*/
void WS2812_0_Code(void)
{
	GPIOD->BSRR = GPIO_Pin_4;
	GPIOD->BSRR = GPIO_Pin_4;
	GPIOD->BSRR = GPIO_Pin_4; //250ns
	
	GPIOD->BRR = GPIO_Pin_4;
//	GPIOD->BRR = GPIO_Pin_4;
//	GPIOD->BRR = GPIO_Pin_4;
//	GPIOD->BRR = GPIO_Pin_4;
//	GPIOD->BRR = GPIO_Pin_4;
//	GPIOD->BRR = GPIO_Pin_4;
//	GPIOD->BRR = GPIO_Pin_4;
//	GPIOD->BRR = GPIO_Pin_4; //750ns
}

void WS2812_1_Code(void)
{
	GPIOD->BSRR = GPIO_Pin_4;
	GPIOD->BSRR = GPIO_Pin_4;
	GPIOD->BSRR = GPIO_Pin_4;
	GPIOD->BSRR = GPIO_Pin_4;
	GPIOD->BSRR = GPIO_Pin_4;
	GPIOD->BSRR = GPIO_Pin_4;
	GPIOD->BSRR = GPIO_Pin_4;
	GPIOD->BSRR = GPIO_Pin_4; //750ns
	
	GPIOD->BRR = GPIO_Pin_4;
//	GPIOD->BRR = GPIO_Pin_4;
//	GPIOD->BRR = GPIO_Pin_4;  //250ns 
}
