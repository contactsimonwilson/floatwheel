#ifndef __TASK_H
#define __TASK_H

#include "led.h"
#include "key.h"
#include "ws2812.h"
#include "flag_bit.h"
#include "vesc_uasrt.h"

#define	  CHARGING_VOLTAGE	  		40   		//����ѹ��� ���ڴ�ֵ��Ϊ���������
#define   BATTERY_STRING      		20    		//��ش���
#define   SHUTDOWN_TIME		  		30   		//�ػ�ʱ�� ��λ����
#define   VESC_RPM            		250  		//ת��
#define   VESC_BOOT_TIME      		6000 		//VESC����ʱ�� ��λms
#define   DUTY_CYCLE          		0.7  		//ռ�ձȴ��ڴ�ֵ �����ٵ���
#define   VOLTAGE_RECEIPT     		0.02 		//��ѹ��ִ ��λV
#define   ADC_THRESHOLD             2.0         // Threshold value for footpad activation detection
/*******************************************************************************/
#define   VESC_RPM_WIDTH      		-200 		//ת���ڡ�100֮�䲻��ǰ����л� ����ǰ��׵ƺ�����
#define   LIGHTBAR_BRIGHTNESS_1 	204			// High brightness value (0-255)
#define   LIGHTBAR_BRIGHTNESS_2 	128			// Medium brightness value (0-255)
#define   LIGHTBAR_BRIGHTNESS_3 	30			// Low brightness value (0-255)
#define   CHARGE_CURRENT			0.3         //������ ��λA
#define   CHARGE_CURRENT_L			0.1         //������ ��λA
#define   CHARGE_CURRENT_H			0.24        //������ ��λA
#define   DETECTION_SWITCH_TIME     500         //����л�ʱ�� ��λms
#define   CHARGER_DETECTION_DELAY	1000        //����������ʱ ��λms

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



