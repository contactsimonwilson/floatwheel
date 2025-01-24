#include "usart.h"


/**************************************************
 * @brie   :USART1_Init()
 * @note   :USART1初始化
 * @param  :Baud 波特率
 * @retval :无
 **************************************************/
void USART1_Init(uint32_t Baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//PD1->TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_1);
	//PD6->RX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_1);
	
	USART_InitStructure.USART_BaudRate = Baud;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  //接收中断
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);  //空闲中断
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
}

/**************************************************
 * @brie   :USART1_Send_Byte()
 * @note   :USART1发送一个字节
 * @param  :byte 字节
 * @retval :无
 **************************************************/
void USART1_Send_Byte(uint8_t byte)
{
	while((USART1->ISR & USART_ISR_TXE) == 0);
	USART1->TDR = byte;	
}

/**************************************************
 * @brie   :USART1_Send_Bytes()
 * @note   :USART1发送多个字节
 * @param  :pbyte 字节地址
 * @retval :无
 **************************************************/
void USART1_Send_Bytes(uint8_t *pbyte,uint8_t len)
{
	while(len)
	{
		USART1_Send_Byte(*pbyte);
		pbyte++;
		len--;
	}
}

