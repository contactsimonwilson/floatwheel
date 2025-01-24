#ifndef __USER_CAN_CONFIG_H__
#define __USER_CAN_CONFIG_H__

#define  CAN_MODE_TYPE_NORMAL            1
#define  CAN_MODE_TYPE_LOOPBACK          2
#define  CAN_MODE_TYPE_SILENT            3
#define  CAN_MODE_TYPE_SILENT_LOOPBACK   4
#define  CAN_MODE_TYPE                   CAN_MODE_TYPE_NORMAL

#if(CAN_MODE_TYPE==CAN_MODE_TYPE_NORMAL)
#define  OPERATINGMODE      CAN_Normal_Mode
#elif(CAN_MODE_TYPE==CAN_MODE_TYPE_LOOPBACK)
#define  OPERATINGMODE      CAN_LoopBack_Mode
#elif(CAN_MODE_TYPE==CAN_MODE_TYPE_SILENT)
#define  OPERATINGMODE      CAN_Silent_Mode
#elif(CAN_MODE_TYPE==CAN_MODE_TYPE_SILENT_LOOPBACK)
#define  OPERATINGMODE      CAN_Silent_LoopBack_Mode
#endif

#define  CAN_BAUDRATE_1M            1
#define  CAN_BAUDRATE_500K          2
#define  CAN_BAUDRATE_250K          3
#define  CAN_BAUDRATE_125K          4
#define  CAN_BAUDRATE               CAN_BAUDRATE_500K

#if(CAN_BAUDRATE==CAN_BAUDRATE_1M)
#define   CAN_BIT_RSJW              CAN_RSJW_1tq
#define   CAN_BIT_BS1               CAN_TBS1_5tq
#define   CAN_BIT_BS2               CAN_TBS2_2tq
#define   CAN_BAUDRATEPRESCALER     2 
#elif(CAN_BAUDRATE==CAN_BAUDRATE_500K)
#define   CAN_BIT_RSJW              CAN_RSJW_1tq
#define   CAN_BIT_BS1               CAN_TBS1_10tq
#define   CAN_BIT_BS2               CAN_TBS2_5tq
#define   CAN_BAUDRATEPRESCALER     2
#elif(CAN_BAUDRATE==CAN_BAUDRATE_250K)
#define   CAN_BIT_RSJW              CAN_RSJW_1tq
#define   CAN_BIT_BS1               CAN_TBS1_10tq
#define   CAN_BIT_BS2               CAN_TBS2_5tq
#define   CAN_BAUDRATEPRESCALER     4 
#elif(CAN_BAUDRATE==CAN_BAUDRATE_125K)
#define   CAN_BIT_RSJW              CAN_RSJW_1tq
#define   CAN_BIT_BS1               CAN_TBS1_10tq
#define   CAN_BIT_BS2               CAN_TBS2_5tq
#define   CAN_BAUDRATEPRESCALER     8
#endif


#define  CAN_TXDLC_8                     ((uint8_t)8)
#define  CAN_FILTERNUM0                  ((uint8_t)0)
#define  CAN_TX1_SID                     0x0400
#define  CAN_TX2_EID                     0x12345678
#define  CAN_TX_MESSAGE_BUFF_SIZE        2
#define  CAN_RX_MESSAGE_BUFF_SIZE        10

#define  CAN_FILTER_STDID(STDID)         ((STDID&0x7FF)<<5)

#define  CAN_FILTER_EXTID_H(EXTID)       ((uint16_t)  (((EXTID<<3)|0x04)>>16) )
#define  CAN_FILTER_EXTID_L(EXTID)       ((uint16_t)  (( EXTID<<3)|0x04) )

#define  CAN_STD_ID_H_MASK_CARE          0xFFE0
#define  CAN_STD_ID_L_MASK_CARE          0x0000
#define  CAN_STD_ID_H_MASK_DONT_CARE     0x0000
#define  CAN_STD_ID_L_MASK_DONT_CARE     0x0000

#define  CAN_EXT_ID_H_MASK_CARE          0xFFFF
#define  CAN_EXT_ID_L_MASK_CARE          0xFFF8
#define  CAN_EXT_ID_H_MASK_DONT_CARE     0x0000
#define  CAN_EXT_ID_L_MASK_DONT_CARE     0x0000


typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} Status;


//extern uint32_t CAN_Tx_Interval_Time;
extern uint8_t CAN_Tx_Index;
extern CanRxMessage CAN_RxMessage[CAN_RX_MESSAGE_BUFF_SIZE];
extern uint8_t CAN_RxMessage_Write_Cursor;
extern uint8_t CAN_RxMessage_Read_Cursor;
extern void CAN_Tx_Process(void);
extern CanTxMessage CAN_TxMessages[CAN_TX_MESSAGE_BUFF_SIZE];
extern void CAN_GPIO_Config(void);
extern void CAN_Config(void);
extern uint8_t CANTxMessage(CAN_Module* CANx,CanTxMessage* TxMessage);
extern uint8_t Check_CANRxMessage(CanRxMessage* RxMessage);
extern void Tx_Frame_Message_Init(void);
extern void CAN_Filter_Init(void);
extern void CAN_Recieve_Process(void);

#endif/*__USER_CAN_CONFIG_H__*/

