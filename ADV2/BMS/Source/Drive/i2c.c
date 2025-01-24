#include "i2c.h"

/*
	IIC_SCK -> PB6
	IIC_SDA -> PB7
*/

void I2C_Configure(void)
{
	I2C_InitType  I2C_InitStructure;
	
	I2C_InitStruct(&I2C_InitStructure);
	
	I2C_DeInit(I2C1);
    I2C_InitStructure.BusMode     = I2C_BUSMODE_I2C;
    I2C_InitStructure.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    I2C_InitStructure.OwnAddr1    = 0xD0;	//������I2C��ַ,�ò��������д����Ӱ��
    I2C_InitStructure.AckEnable   = I2C_ACKEN;
    I2C_InitStructure.AddrMode    = I2C_ADDR_MODE_7BIT;
    I2C_InitStructure.ClkSpeed    = 100000;	//100K�������Լ�����оƬ�ֲ�鿴֧�ֵ��ٶȡ�
    I2C_Init(I2C1, &I2C_InitStructure);
	
	I2C_Enable(I2C1, ENABLE);
}

void IIC_Init(void)
{
	GPIO_InitType GPIO_InitStructure;

	GPIO_InitStruct(&GPIO_InitStructure);
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB,ENABLE);
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
	
	GPIO_InitStructure.Pin        	  = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_Slew_Rate_High;
    GPIO_InitStructure.GPIO_Mode  	  = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF1_I2C1;
    GPIO_InitStructure.GPIO_Pull 	  = GPIO_Pull_Up;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	
	I2C_DeInit(I2C1);
	
	I2C_Configure();
}

/**
	* @˵��	IIC����
	* @����	
	* @����ֵ	
	* @ע	
*/
void IIC_Wakeup(void)
{

	GPIO_InitType  GPIO_InitStructure; 
	
	GPIO_InitStruct(&GPIO_InitStructure);
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB,ENABLE);
	
	GPIO_InitStructure.Pin          = GPIO_PIN_6|GPIO_PIN_7;	
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  	= GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOB,GPIO_PIN_6);//�����źţ�SCL>SDA 2V
	GPIO_ResetBits(GPIOB,GPIO_PIN_7);//
	
	User_Delay_xms(5);

	IIC_Init();//����IICͨ��
}

#define I2C_LONG_TIMEOUT       ((u32)0x10000)

/**
	* @˵��	��д�Ĵ������ݴ��뻺��
	* @����	��ַ���������顢����
	* @����ֵ	�ɹ�/ʧ��
	* @ע	
*/
bool IIC_TransferDataRaw(u8 *writeData,u16 writeLen,u8 *readData,u16 readLen)
{
	u32 I2C_Wait;
	
	u8 slaveRdAddr=writeData[0];
	
	if(writeLen<2)
	{
		return ERROR;
	}		

	//��ʱ�ȴ�	
	//���IIC�������Ƿ�æ(������������߶��ͨ�ſ���ʡ�ԣ�
	for(I2C_Wait=I2C_LONG_TIMEOUT<<1;I2C_GetFlag(I2C1,I2C_FLAG_BUSY);I2C_Wait--)
	{
		if(I2C_Wait==0)
		{
			I2C_DeInit(I2C1);
			I2C_Configure();//���³�ʼ��IIC���Խ��IIC����״̬
			return ERROR;
		}	
	}
	
	I2C_GenerateStart(I2C1, ENABLE);//����START�ź�
	//��ʱ�ȴ�
	/*EV5,��ģʽ*/
	for(I2C_Wait=I2C_LONG_TIMEOUT;!I2C_CheckEvent(I2C1,I2C_EVT_MASTER_MODE_FLAG);I2C_Wait--)
	{
		if(I2C_Wait==0)
		{
			label_timeout:
			I2C_GenerateStop(I2C1,ENABLE);//�˳�ʱȷ���ر�I2C1����
			return ERROR;
		}
	}

	I2C_SendAddr7bit(I2C1, slaveRdAddr, I2C_DIRECTION_SEND);
	//��ʱ�ȴ�
	for(I2C_Wait=I2C_LONG_TIMEOUT;!I2C_CheckEvent(I2C1,I2C_EVT_MASTER_TXMODE_FLAG);I2C_Wait--)
	{//Test on EV6 and clear it
		if(I2C_Wait==0)
		{
			goto label_timeout;
		}			
	}
	
	//I2C_Cmd( I2C1,ENABLE );//Clear EV6 by setting again the PE bit
	while(--writeLen)
	{
		I2C_SendData(I2C1, *++writeData);//�Ĵ�����ַ
		//��ʱ�ȴ�
		for(I2C_Wait=I2C_LONG_TIMEOUT;!I2C_CheckEvent(I2C1,I2C_EVT_MASTER_DATA_SENDED);I2C_Wait--)
		{
			if(I2C_Wait==0)
			{
				goto label_timeout;
			} 
		}
	}	
	
	if(readLen>0)
	{
		I2C_GenerateStart(I2C1, ENABLE);//���η�����ʼ��
		//���EV5�����
		for(I2C_Wait=I2C_LONG_TIMEOUT;!I2C_CheckEvent(I2C1,I2C_EVT_MASTER_MODE_FLAG);I2C_Wait--)
		{
			if(I2C_Wait==0) goto label_timeout;
		}
	
		I2C_SendAddr7bit(I2C1,slaveRdAddr,I2C_DIRECTION_RECV );//�����豸��ַ(8λ�Լ���)
		//I2C_Wait = I2C_LONG_TIMEOUT;//�ȴ�ʱ�临λ
		for(I2C_Wait=I2C_LONG_TIMEOUT;!I2C_CheckEvent(I2C1,I2C_EVT_MASTER_RXMODE_FLAG);I2C_Wait--)
		{//���EV6(��)�����
			if(I2C_Wait==0)
			{
				goto label_timeout;
			}				
		}
	
		if(readLen>1)
		{
			I2C_ConfigAck(I2C1,ENABLE);//ʹ�ܶ�Ӧ��
			
			while(--readLen!=0)
			{
				for(I2C_Wait=I2C_LONG_TIMEOUT;!I2C_CheckEvent(I2C1,I2C_EVT_MASTER_DATA_RECVD_FLAG);I2C_Wait--)
				{
					if(I2C_Wait==0)
					{
						goto label_timeout;
					}						
				} 	
				*readData++=I2C_RecvData(I2C1);
			}
		}
		I2C_ConfigAck(I2C1,DISABLE);//�����һ���ֽڣ�Ҫ�ر�Ӧ��	
		I2C_GenerateStop(I2C1,ENABLE);//�ر�I2C1����
		for(I2C_Wait=I2C_LONG_TIMEOUT;I2C_GetFlag(I2C1,I2C_FLAG_RXDATNE)==RESET;I2C_Wait--)
		{
			if(I2C_Wait==0)
			{
				goto label_timeout;
			}				
		}
		*readData++=I2C_RecvData(I2C1);
	}	
	else
	{
		I2C_ConfigAck(I2C1,DISABLE);//�ر�I2C1����
	}	
	
	return SUCCESS;	
}

