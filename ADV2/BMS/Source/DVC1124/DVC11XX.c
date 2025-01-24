/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.01.20
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			          AFE驱动函数                              		
******************************************************************************/
#include "i2c.h"
#include "DVC11XX.h"
//------------------------------------------------------------------------------
TAFERegs g_AfeRegs;
CleanFlag g_cleanflag;
static u8 I2CTransferBuffer[300];
u8 IIC_SLAVE_ADDRESS;

//---------------------------------------------------------------------------
const u8 CRC8_LOOKUP_TABLE[256] =
{//查表法(生成多项式x8+x2+x+1)
    0x00, 0x07, 0x0e, 0x09, 0x1c, 0x1b, 0x12, 0x15, 0x38, 0x3f, 0x36, 0x31, 0x24, 0x23, 0x2a, 0x2d,
    0x70, 0x77, 0x7e, 0x79, 0x6c, 0x6b, 0x62, 0x65, 0x48, 0x4f, 0x46, 0x41, 0x54, 0x53, 0x5a, 0x5d,
    0xe0, 0xe7, 0xee, 0xe9, 0xfc, 0xfb, 0xf2, 0xf5, 0xd8, 0xdf, 0xd6, 0xd1, 0xc4, 0xc3, 0xca, 0xcd,
    0x90, 0x97, 0x9e, 0x99, 0x8c, 0x8b, 0x82, 0x85, 0xa8, 0xaf, 0xa6, 0xa1, 0xb4, 0xb3, 0xba, 0xbd,
    0xc7, 0xc0, 0xc9, 0xce, 0xdb, 0xdc, 0xd5, 0xd2, 0xff, 0xf8, 0xf1, 0xf6, 0xe3, 0xe4, 0xed, 0xea,
    0xb7, 0xb0, 0xb9, 0xbe, 0xab, 0xac, 0xa5, 0xa2, 0x8f, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9d, 0x9a,
    0x27, 0x20, 0x29, 0x2e, 0x3b, 0x3c, 0x35, 0x32, 0x1f, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0d, 0x0a,
    0x57, 0x50, 0x59, 0x5e, 0x4b, 0x4c, 0x45, 0x42, 0x6f, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7d, 0x7a,
    0x89, 0x8e, 0x87, 0x80, 0x95, 0x92, 0x9b, 0x9c, 0xb1, 0xb6, 0xbf, 0xb8, 0xad, 0xaa, 0xa3, 0xa4,
    0xf9, 0xfe, 0xf7, 0xf0, 0xe5, 0xe2, 0xeb, 0xec, 0xc1, 0xc6, 0xcf, 0xc8, 0xdd, 0xda, 0xd3, 0xd4,
    0x69, 0x6e, 0x67, 0x60, 0x75, 0x72, 0x7b, 0x7c, 0x51, 0x56, 0x5f, 0x58, 0x4d, 0x4a, 0x43, 0x44,
    0x19, 0x1e, 0x17, 0x10, 0x05, 0x02, 0x0b, 0x0c, 0x21, 0x26, 0x2f, 0x28, 0x3d, 0x3a, 0x33, 0x34,
    0x4e, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5c, 0x5b, 0x76, 0x71, 0x78, 0x7f, 0x6a, 0x6d, 0x64, 0x63,
    0x3e, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2c, 0x2b, 0x06, 0x01, 0x08, 0x0f, 0x1a, 0x1d, 0x14, 0x13,
    0xae, 0xa9, 0xa0, 0xa7, 0xb2, 0xb5, 0xbc, 0xbb, 0x96, 0x91, 0x98, 0x9f, 0x8a, 0x8d, 0x84, 0x83,
    0xde, 0xd9, 0xd0, 0xd7, 0xc2, 0xc5, 0xcc, 0xcb, 0xe6, 0xe1, 0xe8, 0xef, 0xfa, 0xfd, 0xf4, 0xf3
};
/**
	* @说明	crc8计算
	* @参数	数据地址、长度
	* @返回值	u8 crc值
	* @注	
*/
u8 calc_crc8(void *dataPtr,u16 dataLen)
{//查表法
	u8 carry = 0;
	while(dataLen--)
	{
		carry = CRC8_LOOKUP_TABLE[carry^(*(u8 *)dataPtr)];
		dataPtr=(u8 *)dataPtr+1;
	}
	return carry;
}

/**
	* @说明	读取寄存器并计算CRC
	* @参数	AFE寄存器起始地址、偏移地址、长度
	* @返回值	成功/失败
	* @注	
*/
bool IIC_ReadDataWithCRC(u8 regAddr,void *dataPtr,u16 dataLen)
{
	u8 dummyWr[4],*src;
	dummyWr[0]=IIC_SLAVE_ADDRESS<<1; //写入设备地址
	dummyWr[1]=regAddr;  //寄存器地址
	
	if(dataLen<=(sizeof(I2CTransferBuffer)<<1) && IIC_TransferDataRaw(dummyWr,2,I2CTransferBuffer,dataLen<<1))
	{  //先写后读
		dummyWr[2]=(IIC_SLAVE_ADDRESS<<1)|0x1;
		dummyWr[3]=I2CTransferBuffer[0];
		if(I2CTransferBuffer[1]==calc_crc8(dummyWr,4))
		{
			int remains;
			if(dataLen>1)
			{
				for(remains=dataLen-1,src=I2CTransferBuffer+2;remains>0;remains--,src+=2)
				{
					if(src[1]!=calc_crc8(src,1))
					{
						return ERROR;//读取失败（CRC错误）
					}
				}
				for(remains=dataLen,src=I2CTransferBuffer;remains>0;remains--,src+=2)
				{
					*(u8 *)dataPtr=*src;
					dataPtr=(u8 *)dataPtr+1;
				}
				return SUCCESS; //读取成功
			}
			else if(dataLen==1)
			{
				*(u8 *)dataPtr=I2CTransferBuffer[0];
				return SUCCESS; //读取成功
			}
		}
	}
	return ERROR;
}
/**
	* @说明	写入寄存器
	* @参数	AFE寄存器起始地址、偏移地址、长度
	* @返回值	成功/失败
	* @注	
*/
bool IIC_WriteDataWithCRC(u8 regAddr,void *dataPtr,u16 dataLen)
{
  u8 *des=I2CTransferBuffer,*src=(u8 *)dataPtr;
  *des++=(IIC_SLAVE_ADDRESS<<1)|0x00; //(从设备设备地址<<)|写操作
  *des++=regAddr;  //寄存器地址
  *des++=*src++;
  *des++=calc_crc8(I2CTransferBuffer,3);
  while(--dataLen>0){
    *des++=*src;
    *des++=calc_crc8(src++,1);
  }
  return IIC_TransferDataRaw(I2CTransferBuffer,(int)(des-I2CTransferBuffer),NULL,0);
}
//---------------------------------------------------------------------------
bool IIC_CheckWrite(u8 regAddr,void *dataPtr,u16 dataLen)
{
	u8 retry;
	for(retry=3;retry>0;retry--)
	{
		if(IIC_WriteDataWithCRC(regAddr,dataPtr,dataLen))
		{
			if(IIC_ReadDataWithCRC(regAddr,I2CTransferBuffer,dataLen) && memcmp(I2CTransferBuffer,dataPtr,dataLen)==0)
			{
				return SUCCESS;
			}				
			else 
			{
				User_Delay_us(100);
			}
		}
	}
	return ERROR;
}

/**
	* @说明	AFE数据读取
	* @参数	AFE寄存器起始地址、长度
	* @返回值	成功/失败
	* @注	
*/
bool DVC11XX_ReadRegs(u8 regAddr,u8 regLen)
{
	int retry;
	for(retry=3;retry>0;retry--)
	{
		if(IIC_ReadDataWithCRC(regAddr,(u8 *)&g_AfeRegs+regAddr, regLen))
		{
			return SUCCESS;
		}
		else 
		{
			User_Delay_us(5);
		}
	}
	return ERROR;
}

/**
	* @说明	AFE数据写入
	* @参数	AFE寄存器起始地址、长度
	* @返回值	成功/失败
	* @注	
*/
bool DVC11XX_WriteRegs(u8 regAddr,u8 regLen)
{
	int retry;
	for(retry=3;retry>0;retry--)
	{
		if(IIC_WriteDataWithCRC(regAddr,(u8 *)&g_AfeRegs+regAddr,regLen))
		{
			return SUCCESS;
		}
		else
		{
			User_Delay_us(5);
		}			
	}
	return ERROR;
}
//------------------------------------------------------------------------------
//通过IIC发送指令，强制AFE芯片进入休眠状态
void DVC11XX_ForceSleep(void)
{
	g_AfeRegs.R1.CST=0x0f;
	DVC11XX_WriteRegs(AFE_ADDR_R(1),1);
}
//------------------------------------------------------------------------------

