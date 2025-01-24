#ifndef CELLBALANCE_H__
#define CELLBALANCE_H__

#include "DVC11XX.h"
#include "Voltage.h"
#include "Temperature.h"

#define uiBalanceVolDiff  	500		//���⿪��ѹ����ֵ
#define uiBalanceVol 		2000	//������С��о��ѹ
#define	uiBalanceVol_max	4150	//��������о��ѹ

extern u32 newBals;

float DVC11XX_Calc_ChipTemp(void);
void Balance_Contrl(u32 vlaue);
void OverTempProtect(u8 temp);
void BalanceProcess(void);
void CalcuVolMaxMin(void);

#endif

