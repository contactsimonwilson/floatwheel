#ifndef __DVC1124_INIT_H
#define __DVC1124_INIT_H

#include "n32l40x.h"
#include "i2c.h"
#include "DVC11XX.h"
#include "Temperature.h"

#pragma pack (push,1)



//��Ҫ���õĲ���
typedef struct
{
	uint8_t C1OW_0x56:2;		//CADC CC1 ����ʱ�����λ
	uint8_t	RES_0x56:6;			//����
	uint8_t OCD1T_0x59;			//1���ŵ����������ֵ�Ĵ���,��ֵ��ѹ=OCD1T��0.25mV	
	uint8_t OCC1T_0x5A;			//1��������������ֵ�Ĵ���,��ֵ��ѹ=OCC1T��0.25mV
	uint8_t OCD1D_0x5B;			//1���ŵ���������ӳټĴ���,�ӳ�ʱ��=(OCD1D+1)��8ms
	uint8_t OCC1D_0x5C;			//1�������������ӳټĴ���,�ӳ�ʱ��=(OCC1D+1)��8ms
	uint8_t OCD2T_0x5E:6;		//2���ŵ����������ֵ�Ĵ���,��ֵ��ѹ=(OCD2T+1)��4mV
	uint8_t	RES_0x5E:2;			//����
	uint8_t OCC2T_0x5F:6;		//2��������������ֵ�Ĵ�������ֵ��ѹ=(OCC2T+1)��4mV
	uint8_t RES_0x5F:2;			//����
	uint8_t OCD2D_0x60;			//2���ŵ���������ӳټĴ���,�ӳ�ʱ��=(OCD2D+1)��4ms
	uint8_t OCC2D_0x61;			//2�������������ӳټĴ���,�ӳ�ʱ��=(OCC2D+1)��4ms
	uint8_t SCDT_0x62:6;		//�ŵ��·������ֵ�Ĵ���,��ֵ��ѹ=SCDT��10mV
	uint8_t RES_0x62:2;			//����
	uint8_t SCDD_0x63;			//�ŵ��·�����ӳټĴ���,�ӳ�ʱ��=SCDD��7.81��s
	uint8_t COVT_H_0x70;		//��ع�ѹ�����Ĵ���
	uint8_t COVT_L_0x71:4;		//��ֵ��ѹ=COVT��1mV+500mV	
	uint8_t COVD_0x71:4;		//��ع�ѹ�����ӳٿ���λ 
	uint8_t CUVT_H_0x72;		//��ѹǷѹ�����Ĵ���
	uint8_t CUVT_L_0x73:4;		//��ֵ��ѹ=CUVT��1mV
	uint8_t	CUVD_0x73:4;		//���Ƿѹ�����ӳٿ���λ	
}DVC1124_Config_Type;

#pragma pack (pop)

void DVC1124_Init(void);

#endif

