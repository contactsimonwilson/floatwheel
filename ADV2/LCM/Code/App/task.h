#ifndef __TASK_H
#define __TASK_H

#include "led.h"
#include "key.h"
#include "ws2812.h"
#include "flag_bit.h"
#include "vesc_uasrt.h"

#define	  CHARGING_VOLTAGE	  		3.0   		//充电电压检测 小于此值认为充电器插入
#define   BATTERY_STRING      		20    		//电池串数
#define   SHUTDOWN_TIME		  		30   		//关机时间 单位分钟
#define   VESC_RPM            		250  		//转速
#define   VESC_BOOT_TIME      		6000 		//VESC开机时间 单位ms
#define   DUTY_CYCLE          		0.7  		//占空比大于此值 哔哔哔的响
#define   VOLTAGE_RECEIPT     		0.02 		//电压回执 单位V
/*******************************************************************************/
#define   VESC_RPM_WIDTH      		-200 		//转速在±100之间不做前后灯切换 保持前面白灯后面红灯
#define   WS2812_1_BRIGHTNESS 		204			//WS2812 1挡亮度 （0-255）
#define   WS2812_2_BRIGHTNESS 		128			//WS2812 2挡亮度 （0-255）
#define   WS2812_3_BRIGHTNESS 		30			//WS2812 3挡亮度 （0-255）
#define   WS2812_4_BRIGHTNESS 		0			//WS2812 3挡亮度 （0-255）
#define   CHARGE_CURRENT			0.3         //充电电流 单位A
#define   CHARGE_CURRENT_L			0.1         //充电电流 单位A
#define   CHARGE_CURRENT_H			0.24        //充电电流 单位A
#define   DETECTION_SWITCH_TIME     500         //检测切换时间 单位ms
#define   CHARGER_DETECTION_DELAY	1000        //充电器检测延时 单位ms

void LED_Task(void);
void KEY1_Task(void);
void WS2812_Task(void);
void Power_Task(void);
void Charge_Task(void);
void Flashlight_Task(void);
void Buzzer_Task(void);
void Usart_Task(void);
void ADC_Task(void);
void Conditional_Judgment(void);
void Flashlight_Detection(void);

#endif



