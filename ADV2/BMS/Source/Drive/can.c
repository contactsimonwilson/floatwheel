#include "can.h"

/*
	CAN_TX -> PA12
	CAN_RX -> PA11 
*/

void CANM_Init(void)
{
    GPIO_InitType GPIO_InitStructure;

	GPIO_InitStruct(&GPIO_InitStructure);
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO , ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA , ENABLE);

//	GPIO_Pin_Remap_Set(GPIOA_PORT_SOURCE,GPIO_PIN_SOURCE4,GPIO_AF11_CAN);
//	GPIO_Pin_Remap_Set(GPIOA_PORT_SOURCE,GPIO_PIN_SOURCE5,GPIO_AF11_CAN);
	
    GPIO_InitStructure.Pin       = GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_CAN;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin        = GPIO_PIN_12;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}	

void CAN_Config(void)
{
	CAN_InitType        CAN_InitStructure;
	CAN_FilterInitType  CAN_FilterInitStructure;
	NVIC_InitType 		NVIC_InitStructure;
	
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN, ENABLE);
	
	CAN_DeInit(CAN);
    CAN_InitStruct(&CAN_InitStructure);
    /* CAN cell init */
	CAN_InitStructure.TTCM              = DISABLE;
    CAN_InitStructure.ABOM              = DISABLE;
    CAN_InitStructure.AWKUM             = DISABLE;
    CAN_InitStructure.NART              = DISABLE;
    CAN_InitStructure.RFLM              = DISABLE;
    CAN_InitStructure.TXFP              = ENABLE;
    CAN_InitStructure.OperatingMode     = CAN_Normal_Mode;
    CAN_InitStructure.RSJW              = CAN_RSJW_1tq;
    CAN_InitStructure.TBS1              = CAN_TBS1_10tq;
    CAN_InitStructure.TBS2              = CAN_TBS2_5tq;
    CAN_InitStructure.BaudRatePrescaler = 2;
    
    /*Initializes the CAN */
    CAN_Init(CAN, &CAN_InitStructure);
    
    /* CAN filter init */
    CAN_FilterInitStructure.Filter_Num            = 0;
    CAN_FilterInitStructure.Filter_Mode           = CAN_Filter_IdMaskMode;
    CAN_FilterInitStructure.Filter_Scale          = CAN_Filter_32bitScale;
	
    CAN_FilterInitStructure.Filter_HighId         = 0x0000;
    CAN_FilterInitStructure.Filter_LowId          = 0x0000;
	
    CAN_FilterInitStructure.FilterMask_HighId     = 0x0000;
    CAN_FilterInitStructure.FilterMask_LowId      = 0x0000;
	
    CAN_FilterInitStructure.Filter_FIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.Filter_Act            = ENABLE;
    CAN_InitFilter(&CAN_FilterInitStructure);
	
    /* IT Configuration for CAN */  
    CAN_INTConfig(CAN, CAN_INT_FMP0, ENABLE);
    
    /* NVIC configure */
    NVIC_InitStructure.NVIC_IRQChannel                   = CAN_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
