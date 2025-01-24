#ifndef __VESC_CAN
#define __VESC_CAN

#include "n32l40x.h"
#include "datatypes.h"

typedef union
{
	float f;
	uint8_t i[4];
}FLOAT_INT_TYP;

typedef union
{
	uint32_t i;
	uint32_t res:12;
	uint32_t b20:1;
	uint32_t b19:1;
	uint32_t b18:1;
	uint32_t b17:1;
	uint32_t b16:1;
	uint32_t b15:1;
	uint32_t b14:1;
	uint32_t b13:1;
	uint32_t b12:1;
	uint32_t b11:1;
	uint32_t b10:1;
	uint32_t b9:1;
	uint32_t b8:1;
	uint32_t b7:1;
	uint32_t b6:1;
	uint32_t b5:1;
	uint32_t b4:1;
	uint32_t b3:1;
	uint32_t b2:1;
	uint32_t b1:1;
}INT32_BIT_TYP;

typedef struct
{
	FLOAT_INT_TYP 	Total_Voltage;			//总电压
	FLOAT_INT_TYP 	Charge_Input_Voltage;	//充电器电压
}CAN_BMS_V_TOT;

typedef struct
{
	FLOAT_INT_TYP 	Input_Current;			//输入电流
	FLOAT_INT_TYP 	Input_Current_BMS_IC;	//BMS_IC电流
}CAN_BMS_I;

typedef struct
{
	FLOAT_INT_TYP 	Ah_Counter;				//电池毫安时
	FLOAT_INT_TYP 	Wh_Counter;				//电池W时 
}CAN_BMS_AH_WH;

typedef struct
{
	uint8_t         Group;					//第几组	一帧报文最多设置3组电池电压
	uint8_t			BMS_String;				//BMS串数
	uint16_t		BMS_Single_Voltage[20];	//单节电池电压	扩大1000倍发送
}CAN_BMS_V_CELL;

typedef struct
{
	uint8_t			BMS_String;				//BMS串数
	INT32_BIT_TYP	BMS_BAT;				//单节电池状态
}CAN_BMS_BAL;

typedef struct
{
	uint8_t         Group;					//第几组	一帧报文最多设置3组电池电压
	uint16_t		BMS_Single_Temp[10];	//电池温度	扩大100倍发送
}CAN_BMS_TEMPS;

typedef struct
{
	uint16_t 		Humidity;				//湿度	0-10000(0%-100%);
	int16_t			Temp_Hum_Sensor;		//温度	-10000-10000(-100°-100°)
	int16_t			Temp_IC;				//IC温度
}CAN_BMS_HUM;

typedef struct
{
	uint16_t		V_Cell_Min;				//单节电池最低电压 扩大1000倍发送
	uint16_t		V_Cell_Max;				//单节电池最高电压 扩大1000倍发送
	uint8_t 		Soc;					//0-255(0%-100%) 充电状态
	uint8_t			Soh;					//0-255(0%-100%) 健康状态
	uint8_t			T_Cell_Max;				//单节电池最大温度
	uint8_t			Stat;					//
}CAN_BMS_SOC_SOH_TEMP_STAT;

typedef struct
{
	FLOAT_INT_TYP	Ah_Charge_Total;		//充电安时
	FLOAT_INT_TYP   Wh_Charge_Total;		//充电瓦时
}CAN_BMS_AH_WH_CHG_TOTAL;

typedef struct
{
	FLOAT_INT_TYP	Ah_Discharge_Total;		//安时
	FLOAT_INT_TYP   Wh_Discharge_Total;		//瓦时
}CAN_BMS_AH_WH_DIS_TOTAL;

typedef struct
{
	CAN_BMS_V_TOT 	*pBMS_V_TOT;
	CAN_BMS_I		*pBMS_I;
	CAN_BMS_AH_WH	*pBMS_AH_WH;
	CAN_BMS_V_CELL	*pBMS_V_CELL;
	CAN_BMS_BAL		*pBMS_BAL;
	CAN_BMS_TEMPS 	*pBMS_TEMPS;
	CAN_BMS_HUM		*pBMS_HUM;
	CAN_BMS_SOC_SOH_TEMP_STAT	*pBMS_SOC_SOH_TEMP_STAT;
	CAN_BMS_AH_WH_CHG_TOTAL		*pBMS_AH_WH_CHG_TOTAL;
	CAN_BMS_AH_WH_DIS_TOTAL		*pBMS_AH_WH_DIS_TOTAL;
	CAN_PACKET_ID 	VESC_CAN_CMD;
}VESC_CAN_TYPE;

typedef struct
{
	FLOAT_INT_TYP 	Total_Voltage;			//总电压
	FLOAT_INT_TYP 	Charge_Input_Voltage;	//充电器电压	
	FLOAT_INT_TYP 	Input_Current;			//输入电流
	FLOAT_INT_TYP 	Input_Current_BMS_IC;	//BMS_IC电流
	FLOAT_INT_TYP 	Ah_Counter;				//电池毫安时
	FLOAT_INT_TYP 	Wh_Counter;				//电池W时 
	uint16_t 		Humidity;				//湿度	0-10000(0%-100%);
	int16_t			Temp_Hum_Sensor;		//温度	-10000-10000(-100°-100°)
	int16_t			Temp_IC;				//IC温度
	uint16_t		V_Cell_Min;				//单节电池最低电压 扩大1000倍发送
	uint16_t		V_Cell_Max;				//单节电池最高电压 扩大1000倍发送
	uint8_t 		Soc;					//0-255(0%-100%)
	uint8_t			Soh;					//0-255(0%-100%)
	uint8_t			T_Cell_Max;				//单节电池最大温度
	uint8_t			Stat;					//
	FLOAT_INT_TYP	Ah_Charge_Total;		//安时
	FLOAT_INT_TYP   Wh_Charge_Total;		//瓦时
	FLOAT_INT_TYP	Ah_Discharge_Total;		//安时
	FLOAT_INT_TYP   Wh_Discharge_Total;		//瓦时
	uint8_t         Group;					//第几组	一帧报文最多设置3组电池电压
	uint8_t			BMS_String;				//BMS串数
	uint16_t		BMS_Single_Voltage[20];	//单节电池电压	扩大1000倍发送
	uint16_t		BMS_Single_Temp[10];	//电池温度	扩大100倍发送
	uint32_t		BMS_Single_Stat;		//单节电池状态	
	
	CAN_PACKET_ID 	VESC_CAN_CMD;
	
}VESC_CAN_TYP;

extern VESC_CAN_TYPE VESC_CAN_DATA;

void VESC_Set_BMS_V_TOT(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);
void VESC_Set_BMS_I(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);
void VESC_Set_BMS_AH_WH(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);
void VESC_Set_BMS_V_CELL(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);
void VESC_Set_BMS_BAL(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);
void VESC_Set_BMS_TEMPS(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);
void VESC_Set_BMS_HUM(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);
void VESC_Set_BMS_SOC_SOH_TEMP_STAT(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);
void VESC_Set_BMS_AH_WH_CHG_TOTAL(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);
void VESC_Set_BMS_AH_WH_DIS_TOTAL(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data);

typedef struct
{
	int32_t Rpm;			//转速
	float	Duty_Cycle;		//占空比
	float	Total_Current;	//总电流
}CAN_STATUS;

typedef struct
{
	float	Amp_Hours_Charged;	//充电的安时
	float	Amp_Hours;			//消耗的安时
}CAN_STATUS_2;

typedef struct
{
	float	Watt_Hours_Charged;	//充电的瓦时
	float	Watt_Hours;			//消耗的瓦时
}CAN_STATUS_3;

typedef struct
{
	float 	PID_Pos;				//不清楚数据类型
	float 	Total_Input_Current;	//输入总电流
	float 	Motor_Temp;				//电机温度
	float 	MOSFET_Temp;			//MOS管温度
}CAN_STATUS_4;

typedef struct
{
	float 	Input_Voltage;		//输入电压
	int32_t Tachometer_Value;	//转速表?不确定
}CAN_STATUS_5;

typedef struct
{
	CAN_STATUS 		*pSTATUS;
	CAN_STATUS_2	*pSTATUS_2;
	CAN_STATUS_3	*pSTATUS_3;
	CAN_STATUS_4	*pSTATUS_4;
	CAN_STATUS_5	*pSTATUS_5;
}VESC_CAN_RX_TYPE;

extern VESC_CAN_RX_TYPE VESC_CAN_RX_DATA;

void VESC_CAN_RX_Inte(CanRxMessage *can_rx_struct,VESC_CAN_RX_TYPE *vesc_can_rx_data);

#endif



