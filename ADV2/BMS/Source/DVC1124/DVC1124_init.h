#ifndef __DVC1124_INIT_H
#define __DVC1124_INIT_H

#include "n32l40x.h"
#include "i2c.h"
#include "DVC11XX.h"
#include "Temperature.h"

#pragma pack (push,1)



//需要配置的参数
typedef struct
{
	uint8_t C1OW_0x56:2;		//CADC CC1 测量时间控制位
	uint8_t	RES_0x56:6;			//保留
	uint8_t OCD1T_0x59;			//1级放电过流保护阈值寄存器,阈值电压=OCD1T×0.25mV	
	uint8_t OCC1T_0x5A;			//1级充电过流保护阈值寄存器,阈值电压=OCC1T×0.25mV
	uint8_t OCD1D_0x5B;			//1级放电过流保护延迟寄存器,延迟时间=(OCD1D+1)×8ms
	uint8_t OCC1D_0x5C;			//1级充电过流保护延迟寄存器,延迟时间=(OCC1D+1)×8ms
	uint8_t OCD2T_0x5E:6;		//2级放电过流保护阈值寄存器,阈值电压=(OCD2T+1)×4mV
	uint8_t	RES_0x5E:2;			//保留
	uint8_t OCC2T_0x5F:6;		//2级充电过流保护阈值寄存器，阈值电压=(OCC2T+1)×4mV
	uint8_t RES_0x5F:2;			//保留
	uint8_t OCD2D_0x60;			//2级放电过流保护延迟寄存器,延迟时间=(OCD2D+1)×4ms
	uint8_t OCC2D_0x61;			//2级充电过流保护延迟寄存器,延迟时间=(OCC2D+1)×4ms
	uint8_t SCDT_0x62:6;		//放电短路保护阈值寄存器,阈值电压=SCDT×10mV
	uint8_t RES_0x62:2;			//保留
	uint8_t SCDD_0x63;			//放电短路保护延迟寄存器,延迟时间=SCDD×7.81μs
	uint8_t COVT_H_0x70;		//电池过压保护寄存器
	uint8_t COVT_L_0x71:4;		//阈值电压=COVT×1mV+500mV	
	uint8_t COVD_0x71:4;		//电池过压保护延迟控制位 
	uint8_t CUVT_H_0x72;		//电压欠压保护寄存器
	uint8_t CUVT_L_0x73:4;		//阈值电压=CUVT×1mV
	uint8_t	CUVD_0x73:4;		//电池欠压保护延迟控制位	
}DVC1124_Config_Type;

#pragma pack (pop)

void DVC1124_Init(void);

#endif

