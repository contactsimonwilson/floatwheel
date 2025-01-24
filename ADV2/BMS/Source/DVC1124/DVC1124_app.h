#ifndef __DVC1124_APP_H
#define __DVC1124_APP_H

#include "n32l40x.h"
#include "i2c.h"
#include "DVC11XX.h"
#include "flag.h"
#include "Voltage.h"
#include "vesc_can.h"
#include "Temperature.h"
#include "Current.h"
#include "CellBalance.h"
#include "DVC1124_init.h"

typedef struct
{
	float 		Voltage;	//电池电压
	uint16_t	Single_Voltage[20];
	float 		IC_Temp;	//芯片温度
	float		GP1_Temp;	//GP1温度电阻
	float		GP3_Temp;	//GP3温度电阻
	float		GP4_Temp;	//GP4温度电阻
	float       Current_CC1;//CC1电流
	float       Current_CC2;//CC2电流
}DVC1124_Type;

extern DVC1124_Type	DVC_1124;

void DVC1124_Task(void);
	
#endif

