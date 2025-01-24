#ifndef CELLBALANCE_H__
#define CELLBALANCE_H__

#include "DVC11XX.h"
#include "Voltage.h"
#include "Temperature.h"

#define uiBalanceVolDiff  	500		//均衡开启压差阈值
#define uiBalanceVol 		2000	//均衡最小电芯电压
#define	uiBalanceVol_max	4150	//均衡最大电芯电压

extern u32 newBals;

float DVC11XX_Calc_ChipTemp(void);
void Balance_Contrl(u32 vlaue);
void OverTempProtect(u8 temp);
void BalanceProcess(void);
void CalcuVolMaxMin(void);

#endif

