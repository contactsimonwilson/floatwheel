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
		Power = 0;	//Just turned on [�տ���]
		Power = 1;	//Power on [����]
		Power = 2;	//Boot completed [�������]
		Power = 3;	//Shut down [�ػ�]
		Power = 4;	//Continue balance charging after shutting down [�ػ������ƽ���]
	*/
	uint8_t Power:3;
	/*
		1:button to turn on, 
		0:button to turn off [1�������� 0�����ػ�]
	*/
	uint8_t Key_Boot:1;
	/*
		1:The charger is on, 
		0:The charger is off [1���������	0������ػ�]
	*/
	uint8_t Charger_Boot:1;
	/*
		0:The charger is ready to be turned on, 
		1:The charger is turned on [0�����׼������	1����������]
	*/
	uint8_t Charger_ON:1;
	/*
		0:No short circuit occurs, 
		1:Short circuit occurs [0û�з�����· 1������·]
	*/
	uint8_t Short_Circuit:1;
	/*
		0:Not warped, 
		1:Warped [0����ͷ	1��ͷ]
	*/
	uint8_t Cock_Head:1;
	
	/*
		0:No overvoltage, 
		1:Overvoltage occurs [0û�й�ѹ 1������ѹ]
	*/
	uint8_t Overvoltage:1;
	/*
		0:No undervoltage 
		1:Undervoltage occurs [0û��Ƿѹ 1����Ƿѹ]
	*/
	uint8_t Undervoltage:1;
	/*
		0:No charging overcurrent, 
		1:Charging overcurrent occurs [0û�г�����	1����������]
	*/
	uint8_t Charging_Overcurrent:1;
	/*
		0:No discharge overcurrent, 
		1:Discharge overcurrent occurs [0û�зŵ���� 1�����ŵ����]
	*/
	uint8_t Electric_Discharge_Overcurrent:1;
	/*
		0:No overheating, 
		1:Overheating occurs [0û�й��� 1��������]
	*/
	uint8_t Overtemperature:1;
	/*
		0:No low temperature,
		1:Low temperature occurs [0û�е����� 1��������]
	*/
	uint8_t Lowtemperature:1;
	/*
		0:No software reset 
		1:Software reset occurs [0û�������λ	1���������λ]
	*/
	uint8_t Software_Reset:1;
	
	uint8_t	Res2;
	
}Flag_Type;

extern Flag_Type Flag;
extern uint16_t LED_Flicker_Time;

#endif

