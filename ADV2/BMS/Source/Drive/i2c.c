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
    I2C_InitStructure.OwnAddr1    = 0xD0;	//主机的I2C地址,用不到则随便写，无影响
    I2C_InitStructure.AckEnable   = I2C_ACKEN;
    I2C_InitStructure.AddrMode    = I2C_ADDR_MODE_7BIT;
    I2C_InitStructure.ClkSpeed    = 100000;	//100K，根据自己所用芯片手册查看支持的速度。
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
	* @说明	IIC唤醒
	* @参数	
	* @返回值	
	* @注	
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

	GPIO_SetBits(GPIOB,GPIO_PIN_6);//唤醒信号：SCL>SDA 2V
	GPIO_ResetBits(GPIOB,GPIO_PIN_7);//
	
	User_Delay_xms(5);

	IIC_Init();//重启IIC通信
}

#define I2C_LONG_TIMEOUT       ((u32)0x10000)

/**
	* @说明	读写寄存器数据存入缓存
	* @参数	地址、缓存数组、长度
	* @返回值	成功/失败
	* @注	
*/
bool IIC_TransferDataRaw(u8 *writeData,u16 writeLen,u8 *readData,u16 readLen)
{
	u32 I2C_Wait;
	
	u8 slaveRdAddr=writeData[0];
	
	if(writeLen<2)
	{
		return ERROR;
	}		

	//超时等待	
	//检测IIC控制器是否忙(如果不存在总线多机通信可以省略）
	for(I2C_Wait=I2C_LONG_TIMEOUT<<1;I2C_GetFlag(I2C1,I2C_FLAG_BUSY);I2C_Wait--)
	{
		if(I2C_Wait==0)
		{
			I2C_DeInit(I2C1);
			I2C_Configure();//重新初始化IIC，以解除IIC死锁状态
			return ERROR;
		}	
	}
	
	I2C_GenerateStart(I2C1, ENABLE);//发送START信号
	//超时等待
	/*EV5,主模式*/
	for(I2C_Wait=I2C_LONG_TIMEOUT;!I2C_CheckEvent(I2C1,I2C_EVT_MASTER_MODE_FLAG);I2C_Wait--)
	{
		if(I2C_Wait==0)
		{
			label_timeout:
			I2C_GenerateStop(I2C1,ENABLE);//退出时确保关闭I2C1总线
			return ERROR;
		}
	}

	I2C_SendAddr7bit(I2C1, slaveRdAddr, I2C_DIRECTION_SEND);
	//超时等待
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
		I2C_SendData(I2C1, *++writeData);//寄存器地址
		//超时等待
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
		I2C_GenerateStart(I2C1, ENABLE);//二次发送起始符
		//检查EV5并清除
		for(I2C_Wait=I2C_LONG_TIMEOUT;!I2C_CheckEvent(I2C1,I2C_EVT_MASTER_MODE_FLAG);I2C_Wait--)
		{
			if(I2C_Wait==0) goto label_timeout;
		}
	
		I2C_SendAddr7bit(I2C1,slaveRdAddr,I2C_DIRECTION_RECV );//发送设备地址(8位以及读)
		//I2C_Wait = I2C_LONG_TIMEOUT;//等待时间复位
		for(I2C_Wait=I2C_LONG_TIMEOUT;!I2C_CheckEvent(I2C1,I2C_EVT_MASTER_RXMODE_FLAG);I2C_Wait--)
		{//检查EV6(读)并清除
			if(I2C_Wait==0)
			{
				goto label_timeout;
			}				
		}
	
		if(readLen>1)
		{
			I2C_ConfigAck(I2C1,ENABLE);//使能读应答
			
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
		I2C_ConfigAck(I2C1,DISABLE);//读最后一个字节（要关闭应答）	
		I2C_GenerateStop(I2C1,ENABLE);//关闭I2C1总线
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
		I2C_ConfigAck(I2C1,DISABLE);//关闭I2C1总线
	}	
	
	return SUCCESS;	
}

