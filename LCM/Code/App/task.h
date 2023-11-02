#ifndef __TASK_H
#define __TASK_H

#include "led.h"
#include "key.h"
#include "ws2812.h"
#include "flag_bit.h"
#include "vesc_uasrt.h"

#define	  CHARGING_VOLTAGE	  		40
#define   BATTERY_STRING      		20
#define   SHUTDOWN_TIME		  		20
#define   VESC_RPM            		250
#define   VESC_BOOT_TIME      		4000
#define   DUTY_CYCLE          		0.9
#define   VOLTAGE_RECEIPT     		0.02
/*******************************************************************************/
#define   VESC_RPM_WIDTH      		-200
#define   WS2812_1_BRIGHTNESS 		100
#define   WS2812_2_BRIGHTNESS 		60
#define   WS2812_3_BRIGHTNESS 		30
#define   CHARGE_CURRENT			0.3
#define   CHARGE_CURRENT_L			0.1
#define   CHARGE_CURRENT_H			0.24
#define   DETECTION_SWITCH_TIME     500
#define   CHARGER_DETECTION_DELAY	1000

void LED_Task(void);
void KEY1_Task(void);
void WS2812_Task(void);
void Power_Task(void);
void Charge_Task(void);
void Headlights_Task(void);
void Buzzer_Task(void);
void Usart_Task(void);
void ADC_Task(void);
void Conditional_Judgment(void);
void Flashlight_Detection(void);

#endif



