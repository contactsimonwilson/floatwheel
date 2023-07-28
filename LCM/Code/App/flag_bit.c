#include "flag_bit.h"

/*
	Power_Flag = 0; ���ϵ�
	Power_Flag = 1��VESC����
	Power_Flag = 2; VESC�������
	Power_Flag = 3; VESC�ػ�������������ӹ���
*/
uint8_t Power_Flag = 0;
/*
	Charge_Flag = 0; ���ϵ�
	Charge_Flag = 1��׼�����
	Charge_Flag = 2������
	Charge_Flag = 3����ص������
*/
uint8_t Charge_Flag = 0;
///*
//	VESC_Boot_Flag = 0; VESC�ػ�
//	VESC_Boot_Flag = 1��VESC����
//*/
//uint8_t VESC_Boot_Flag = 0;
/*
	Flashlight_Flag = 0; ���ϵ�
	Flashlight_Flag = 1; VESC����
	Flashlight_Flag = 2��VESCǰ��׵ƺ�����(��ת)
	Flashlight_Flag = 3��VESCǰ���ƺ���׵�(��ת)
	Flashlight_Flag = 4; ����10%
*/
uint8_t Flashlight_Flag = 0;
/*
	Brightness_Flag = 0; ���ϵ�
	Brightness_Flag = 1; ��ʼ��������
	Brightness_Flag = 2�����ȵ������
*/
uint8_t Brightness_Flag = 0;
/*
	Lightbar_Mode_Flag = 0; ���ϵ�
	Lightbar_Mode_Flag = 1����ʾ����
	Lightbar_Mode_Flag = 2������ʾ����
*/
uint8_t Lightbar_Mode_Flag = 0;
/*
	Footpad_Activation_Flag = 0; ���ϵ�
	Footpad_Activation_Flag = 1�����5������     �Ҳ�5���Ʋ�����   adc1>ADC_THRESHOLD  adc2<ADC_THRESHOLD
	Footpad_Activation_Flag = 2�����5���Ʋ����� �Ҳ�5������       adc1<ADC_THRESHOLD  adc2>ADC_THRESHOLD
	Footpad_Activation_Flag = 3��10���ƶ�������                    adc1>2.ADC_THRESHOLD  adc2>ADC_THRESHOLD
	Footpad_Activation_Flag = 4��10���ƶ���
*/
uint8_t Footpad_Activation_Flag = 0;
/*
	Power_Display_Flag = 0; ���ϵ�
	Power_Display_Flag = 1�� 4.08V~4.2V 	10���׵�
	Power_Display_Flag = 2�� 4.05V~4.08V 9���׵�
	Power_Display_Flag = 3�� 3.96V~4.05V 8���׵�
	Power_Display_Flag = 4�� 3.87V~3.96V 7���׵�
	Power_Display_Flag = 5�� 3.78V~3.87V 7���׵�
	Power_Display_Flag = 6�� 3.70V~3.78V 5���׵�
	Power_Display_Flag = 7�� 3.62V~3.70V 4���׵�
	Power_Display_Flag = 8�� 3.50V~3.62V 3���׵�
	Power_Display_Flag = 9�� 3.35V~3.50V 2�����
	Power_Display_Flag = 10; 2.80V~3.35V 1�����
*/
uint8_t Power_Display_Flag = 0;
/*
	Buzzer_Flag = 0; ���ϵ�
	Buzzer_Flag = 1������������
	Buzzer_Flag = 2����������
*/
uint8_t Buzzer_Flag = 0;
/*
	Usart_Flag = 0; ���ϵ�
	Usart_Flag = 1�������ɹ�
	Usart_Flag = 2������ʧ�ܻ�ȴ���һ�ν���
*/
uint8_t Usart_Flag = 0;

/*
	VESC����ʱ��
*/
uint16_t VESC_Boot_Time = 0;

/*
	���������ʱ��
*/
uint16_t Buzzer_Time = 0;
/*
	����ʱ
*/
uint16_t Charge_Time = 0;
/*
	������
*/
uint16_t Flashlight_Time = 0;
/*
	����ʱ��
*/
uint16_t Power_Time = 0;
/*
	����ͨ��
*/
uint16_t Usart_Time = 0;
/*
	ADC����ʱ��
*/
uint16_t ADC_Time = 0;
/*
	�ػ�ʱ�� ��
*/
uint16_t Shutdown_Time_S = 0;
/*
	�ػ�ʱ�� ����
*/
uint8_t Shutdown_Time_M = 0;
/*
	��ص�ѹ
*/
//float Battery_Voltage = 0;
/*
	ADC1
*/
float ADC1_Val = 0;
/*
	ADC2
*/
float ADC2_Val = 0;
/*
	ת��
*/
//long VESC_Rpm = 0;
/*
	ĸ�ߵ���
*/
//float AvgInputCurrent = 0;
/*
	ռ�ձ�
*/
//float DutyCycleNow = 0;
/*
	���ڵ�ѹ
*/
float Charge_Voltage = 0;
/*
	Light_Profile = 0 �տ���
	Light_Profile = 1 ���� WS2812���� ��������һ��
	Light_Profile = 2 ����е� WS2812�е� ������������
	Light_Profile = 3 ������� WS2812� ������������
*/
uint8_t Light_Profile = 0;
/*
	WS2812����
*/
uint8_t WS2812_Measure = 0;
/*
	������ bpm 60-180 ��Ӧռ�ձ� 70-100
*/
uint8_t Buzzer_Frequency = 0;
/*
	����˫����̤��û���� �����3S
*/
uint16_t Flashlight_Detection_Time = 0;
/*
	����ѹ�ͳ��ĵ�����ԭʼֵ
*/
float Charge_Current = 0;
/*
	0 ����������
	1 ��������ѹ
*/
uint8_t V_I = 1;
/*
	�����ﵽ�ػ��Ĵ���
*/
uint8_t Shutdown_Cnt = 0;
/*
	��������ʱ��
*/
uint16_t Charger_Detection_1ms = 0;

