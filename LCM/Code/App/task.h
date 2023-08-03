#ifndef __TASK_H
#define __TASK_H

#include "led.h"
#include "key.h"
#include "ws2812.h"
#include "flag_bit.h"
#include "vesc_uasrt.h"

typedef enum
{
	NORMAL,
	RAINBOW
} BOOT_ANIMATION;

typedef enum
{
	P42A,
	DG40
} CELL_TYPE;

typedef enum
{
	LCM,
	VESC,
	OFF
} BUZZER_TYPE;

#define	  CHARGING_VOLTAGE	  		40   		//����ѹ��� ���ڴ�ֵ��Ϊ���������
#define   BATTERY_STRING      		20    		//��ش���
#define   SHUTDOWN_TIME		  		30   		//�ػ�ʱ�� ��λ����
#define   VESC_RPM            		250  		//ת��
#define   VESC_BOOT_TIME      		6000 		// VESC boot time ms
#define   DUTY_CYCLE          		0.7  		//ռ�ձȴ��ڴ�ֵ �����ٵ���
#define   VOLTAGE_RECEIPT     		0.02 		//��ѹ��ִ ��λV
#define   ADC_THRESHOLD_LOWER       2.5         // Threshold value for footpad activation detection
#define   ADC_THRESHOLD_UPPER       2.9         // Threshold value for footpad activation detection
/*******************************************************************************/
#define   VESC_RPM_WIDTH      		-200 		//ת���ڡ�100֮�䲻��ǰ����л� ����ǰ��׵ƺ�����
#define   LIGHTBAR_BRIGHTNESS_1 	140			// High brightness value (0-255)
#define   LIGHTBAR_BRIGHTNESS_2 	70			// Medium brightness value (0-255)
#define   LIGHTBAR_BRIGHTNESS_3 	10			// Low brightness value (0-255)
#define   MAIN_BRIGHTNESS_1			9600		// Low brightness value (0-9999)
#define   MAIN_BRIGHTNESS_2			7200		// Medium brightness value (0-9999)
#define   MAIN_BRIGHTNESS_3			4500		// High brightness value (0-9999)
#define   CHARGE_CURRENT			0.3         //������ ��λA
#define   CHARGE_CURRENT_L			0.1         //������ ��λA
#define   CHARGE_CURRENT_H			0.24        //������ ��λA
#define   DETECTION_SWITCH_TIME     500         //����л�ʱ�� ��λms
#define   CHARGER_DETECTION_DELAY	1000        //����������ʱ ��λms
#define   BOOT_ANIMATION		    NORMAL      // Boot animation
#define   CELL_TYPE                 P42A        // Cell configuration to use for voltage display
#define	  BUZZER_TYPE				LCM		// Change control of buzzer - TODO implement the different options in code
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
void Change_Light_Profile(bool persist);
void Change_Boot_Animation(uint8_t animation);
void Change_Cell_Type(uint8_t type);
void Change_Buzzer_Type(uint8_t type);
//void Change_Cell_Type(uint8_t type, bool get);
//void Change_Boot_Animation(uint8_t animation,bool get); 
#endif



