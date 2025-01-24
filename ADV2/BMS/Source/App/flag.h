#ifndef __FLAG_H
#define __FLAG_H

#include "n32l40x.h"

typedef struct
{
	uint16_t LED;
	uint16_t DVC_1124;
	uint16_t VESC_CAN;
	uint16_t PWR_Boot;		
	uint16_t CHARGER_ON;
	uint16_t Discharge_Overcurrent_Delay;
	uint16_t Charge_Overcurrent_Delay;
	uint16_t Cock_Head;
	uint32_t Power_Off;
	uint16_t DVC_1124_Res;
}Software_Counter_Type;

extern Software_Counter_Type Software_Counter_1ms;

typedef struct
{
	/*
		Power = 0;	//�տ���
		Power = 1;	//����
		Power = 2;	//�������
		Power = 3;	//�ػ�
		Power = 4;	//�ػ������ƽ���
	*/
	uint8_t Power:3;
	/*
		1�������� 	0�����ػ�
	*/
	uint8_t Key_Boot:1;
	/*
		1���������	0������ػ�
	*/
	uint8_t Charger_Boot:1;
	/*
		0�����׼������	1����������
	*/
	uint8_t Charger_ON:1;
	/*
		0û�з�����·	1������·
	*/
	uint8_t Short_Circuit:1;
	/*
		0����ͷ	1��ͷ
	*/
	uint8_t Cock_Head:1;
	
	/*
		0û�й�ѹ	1������ѹ
	*/
	uint8_t Overvoltage:1;
	/*
		0û��Ƿѹ	1����Ƿѹ
	*/
	uint8_t Undervoltage:1;
	/*
		0û�г�����	1����������
	*/
	uint8_t Charging_Overcurrent:1;
	/*
		0û�зŵ����	1�����ŵ����
	*/
	uint8_t Electric_Discharge_Overcurrent:1;
	/*
		0û�й���	1��������
	*/
	uint8_t Overtemperature:1;
	/*
		0û�е�����	1��������
	*/
	uint8_t Lowtemperature:1;
	/*
		0û�������λ	1���������λ
	*/
	uint8_t Software_Reset:1;
	
	uint8_t	Res2;
	
}Flag_Type;

extern Flag_Type Flag;
extern uint16_t LED_Flicker_Time;

#endif

