#include <stdio.h>
#include "n32l40x.h"
#include "User_Can_Config.h"
#include "User_Systick_Config.h"

uint8_t CAN_Tx_Index=0;
CanTxMessage CAN_TxMessage;
CanTxMessage CAN_TxMessages[CAN_TX_MESSAGE_BUFF_SIZE];
CanRxMessage CAN_RxMessage[CAN_RX_MESSAGE_BUFF_SIZE];
uint8_t CAN_RxMessage_Write_Cursor=0;
uint8_t CAN_RxMessage_Read_Cursor=0;
//uint32_t CAN_Tx_Interval_Time=500;

/**
 * @brief  Configures CAN GPIOs
 */
void CAN_GPIO_Config(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configures CAN IOs */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOB, ENABLE);
    /* Configure CAN RX PB8 */
    GPIO_InitStructure.Pin       = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5_CAN;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    /* Configure CAN TX PB9 */
    GPIO_InitStructure.Pin        = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  Configures CAN Filer.
 * @param CAN_BaudRate 10Kbit/s ~ 1Mbit/s
 */
void CAN_Filter_Init(void)
{
    CAN_FilterInitType CAN_FilterInitStructure;
    /* CAN filter init */
    CAN_FilterInitStructure.Filter_Num            = CAN_FILTERNUM0;
    CAN_FilterInitStructure.Filter_Mode           = CAN_Filter_IdMaskMode;
    CAN_FilterInitStructure.Filter_Scale          = CAN_Filter_32bitScale;
    CAN_FilterInitStructure.Filter_HighId         = CAN_FILTER_EXTID_H(0x00005678);
    CAN_FilterInitStructure.Filter_LowId          = CAN_FILTER_EXTID_L(0x00005678);
    CAN_FilterInitStructure.FilterMask_HighId     = CAN_STD_ID_H_MASK_DONT_CARE;
    CAN_FilterInitStructure.FilterMask_LowId      = CAN_STD_ID_L_MASK_DONT_CARE;
    CAN_FilterInitStructure.Filter_FIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.Filter_Act            = ENABLE;
    CAN_InitFilter(&CAN_FilterInitStructure);
    CAN_INTConfig(CAN, CAN_INT_FMP0, ENABLE);
}


/**
 * @brief  CAN Interrupt Configures .
 */
void CAN_NVIC_Config(void)
{
    NVIC_InitType NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = CAN_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**
 * @brief  Configures CAN.
 * @param CAN_BaudRate 10Kbit/s ~ 1Mbit/s
 */
void CAN_Config(void)
{
    CAN_InitType CAN_InitStructure;
    /* Configure CAN */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_CAN, ENABLE);
    /* CAN register init */
    CAN_DeInit(CAN);
    /* Struct init*/
    CAN_InitStruct(&CAN_InitStructure);
    /* CAN cell init */
    CAN_InitStructure.TTCM              = DISABLE;
    CAN_InitStructure.ABOM              = DISABLE;
    CAN_InitStructure.AWKUM             = DISABLE;
    CAN_InitStructure.NART              = DISABLE;
    CAN_InitStructure.RFLM              = DISABLE;
    CAN_InitStructure.TXFP              = ENABLE;
    CAN_InitStructure.OperatingMode     = OPERATINGMODE;
    CAN_InitStructure.RSJW              = CAN_BIT_RSJW;
    CAN_InitStructure.TBS1              = CAN_BIT_BS1;
    CAN_InitStructure.TBS2              = CAN_BIT_BS2;
    CAN_InitStructure.BaudRatePrescaler = CAN_BAUDRATEPRESCALER;
    /*Initializes the CAN */
    CAN_Init(CAN, &CAN_InitStructure);
    CAN_Filter_Init();
    CAN_NVIC_Config();
}

/**
 * @brief  CAN Transmit Message.
 * @param  CAN
 * @param  TxMessage CAN_TxMessage
 * @return The number of the mailbox that is used for transmission or CAN_TxSTS_NoMailBox if there is no empty mailbox.
 */
uint8_t CANTxMessage(CAN_Module* CANx,CanTxMessage* TxMessage)
{
    return CAN_TransmitMessage(CANx, TxMessage);
}



/**
 * @brief  CAN Tx Frame Message Initialize.
 */
void Tx_Frame_Message_Init(void)
{
    uint8_t CAN_Tx_Frame1_Data[8]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    uint8_t CAN_Tx_Frame2_Data[8]={0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01};
    uint8_t i = 0;
    /* Init Transmit frame*/
    CAN_TxMessages[0].StdId   = CAN_TX1_SID; 
    CAN_TxMessages[0].IDE     = CAN_ID_STD;  
    CAN_TxMessages[0].RTR     = CAN_RTRQ_DATA;   
    CAN_TxMessages[0].DLC     = CAN_TXDLC_8;  
    for(i=0;i<CAN_TXDLC_8;i++)
    {
       CAN_TxMessages[0].Data[i]=CAN_Tx_Frame1_Data[i];
    }
    CAN_TxMessages[1].ExtId   = CAN_TX2_EID;
    CAN_TxMessages[1].IDE     = CAN_ID_EXT;
    CAN_TxMessages[1].RTR     = CAN_RTRQ_DATA;
    CAN_TxMessages[1].DLC     = CAN_TXDLC_8;
    for(i=0;i<CAN_TXDLC_8;i++)
    {
       CAN_TxMessages[1].Data[i]=CAN_Tx_Frame2_Data[i];
    }
}


/**
 * @brief  Can Receive Process Function.
 */
void CAN_Recieve_Process(void)
{
    uint8_t i=0;
    if(CAN_RxMessage_Write_Cursor!=CAN_RxMessage_Read_Cursor)
    {
       if(CAN_RxMessage[CAN_RxMessage_Read_Cursor].IDE==CAN_Extended_Id)
       {
          printf("\r\n Receive Frame:%X %X ",\
                  (unsigned int)CAN_RxMessage[CAN_RxMessage_Read_Cursor].ExtId,\
                   CAN_RxMessage[CAN_RxMessage_Read_Cursor].DLC);
       }
       else
       {
          printf("\r\n Receive Frame:%X %X ",\
                  (unsigned int)CAN_RxMessage[CAN_RxMessage_Read_Cursor].StdId,\
                  CAN_RxMessage[CAN_RxMessage_Read_Cursor].DLC);
       }
       for(i=0;i<8;i++) 
          printf(" %X",CAN_RxMessage[CAN_RxMessage_Read_Cursor].Data[i]);
       printf("\r\n");
       if(CAN_RxMessage_Read_Cursor++>=CAN_RX_MESSAGE_BUFF_SIZE)CAN_RxMessage_Read_Cursor=0;
    }
}


/**
 * @brief  Can Receive Process Function.
 */
void CAN_Tx_Process(void)
{
    uint8_t TransmitMailbox = 0;
    uint16_t Time_out       = 0xFFFF;
    static uint32_t CAN_Tx_Interval_Time;
    /* Avoid Other tasks blocking */
    if( User_Time_Read(CAN_Tx_Interval_Time)>TIME_1S) 
    {
       User_Time_Set(&CAN_Tx_Interval_Time);
       /* CAN transmit message */
       TransmitMailbox = CANTxMessage(CAN,&CAN_TxMessages[CAN_Tx_Index%CAN_TX_MESSAGE_BUFF_SIZE]);                                                  
       while ((CAN_TransmitSTS(CAN, TransmitMailbox) != CANTXSTSOK) && (Time_out != 0)) Time_out--;
       Time_out = 0xFFFF;
       CAN_Tx_Index++;
    }
}
