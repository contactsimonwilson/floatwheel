#ifndef __USER_USART_CONFIG_H__
#define __USER_USART_CONFIG_H__

#define    RECEIVE_PROTOCOL_HEAD1    0xFF
#define    RECEIVE_PROTOCOL_HEAD2    0x55
#define    RECEIVE_BUFF_SIZE         20

extern void USART1_Init(void);
extern void NVIC_Configuration(void);


extern uint8_t  Receive_Buff[RECEIVE_BUFF_SIZE];
extern uint8_t  USART1_Receive_Read_Cursor;
extern uint8_t  USART1_Receive_Write_Cursor;
extern void Protocol_Analysis_Head(void);
extern void User_Usart_Send_String(char* ch,uint16_t len);



#endif/*__USER_USART_CONFIG_H__*/


