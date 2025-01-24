#ifndef __I2C_H
#define __I2C_H

#include "n32l40x.h"
#include "User_Delay_Config.h"

void IIC_Init(void);
void IIC_Wakeup(void);
bool IIC_TransferDataRaw(u8 *writeData,u16 writeLen,u8 *readData,u16 readLen);

#endif


