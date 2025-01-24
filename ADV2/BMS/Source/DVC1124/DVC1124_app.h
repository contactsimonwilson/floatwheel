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
	float 		Voltage;	//��ص�ѹ
	uint16_t	Single_Voltage[20];
	float 		IC_Temp;	//оƬ�¶�
	float		GP1_Temp;	//GP1�¶ȵ���
	float		GP3_Temp;	//GP3�¶ȵ���
	float		GP4_Temp;	//GP4�¶ȵ���
	float       Current_CC1;//CC1����
	float       Current_CC2;//CC2����
}DVC1124_Type;

extern DVC1124_Type	DVC_1124;

void DVC1124_Task(void);
	
#endif

