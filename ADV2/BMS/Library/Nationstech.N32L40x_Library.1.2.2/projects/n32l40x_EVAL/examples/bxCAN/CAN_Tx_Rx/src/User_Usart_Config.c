#include <stdio.h>
#include "n32l40x.h"
#include "n32l40x_usart.h"
#include "User_Usart_Config.h"

uint8_t    Receive_Buff[RECEIVE_BUFF_SIZE]={0x00};
uint8_t    USART1_Receive_Read_Cursor=0;
uint8_t    USART1_Receive_Write_Cursor=0;


/**
 * @brief  Configures the nested vectored interrupt controller.
 */
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;
    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel            = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd         = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**
 * @brief  Main program
 */
void USART1_Init(void)
{
    GPIO_InitType GPIO_InitStructure;
    USART_InitType USART_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    //USART_DeInit(USART1); //don't effect
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);
    GPIO_InitStructure.Pin        = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_Slew_Rate_High;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.Pin       = GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_TX | USART_MODE_RX;
    // init uart
    USART_Init(USART1, &USART_InitStructure);
    /* Enable USARTy Receive and Transmit interrupts */
    USART_ConfigInt(USART1, USART_INT_RXDNE, ENABLE);
    // Enable suart
    USART_Enable(USART1, ENABLE);
    USART1_Receive_Read_Cursor=0;
    USART1_Receive_Write_Cursor=0;
}


/* retarget the C library printf function to the USART */
int fputc(int ch, FILE* f)
{
    USART_SendData(USART1, (uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXC) == RESET);
    return (ch);
}
