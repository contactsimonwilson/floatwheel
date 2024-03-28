#ifndef __TASK_H
#define __TASK_H

#include "led.h"
#include "key.h"
#include "ws2812.h"
#include "flag_bit.h"
#include "vesc_uasrt.h"

typedef enum
{
	P42A,
	DG40
} CELL_TYPE;

#define   CELL_TYPE                 P42A        // Cell configuration to use for voltage display (P42A, DG40)
#define	  CHARGING_VOLTAGE	  		40
#define   BATTERY_STRING      		20
#define   SHUTDOWN_TIME		  		20
#define   VESC_RPM            		1000
#define   VESC_BOOT_TIME      		5000
#define   VESC_SHUTDOWN_TIME      	1000
#define   DUTY_CYCLE          		0.9
#define   VOLTAGE_RECEIPT     		0.02
#define	  CHARGE_COMMAND_TIME		1000 		// frequency of notifying the float package of current charge state
/*******************************************************************************/
#define   VESC_RPM_WIDTH      		-200
#define   WS2812_1_BRIGHTNESS 		20
#define   WS2812_2_BRIGHTNESS 		10
#define   WS2812_3_BRIGHTNESS 		5
#define   CHARGE_CURRENT			0.24
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
void VESC_State_Task(void);
void Flashlight_Detection(void);

#endif



