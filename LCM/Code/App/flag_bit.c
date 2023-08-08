#include "flag_bit.h"

/*
	Power_Flag = 0; Just powered on.
	Power_Flag = 1; VESC booting up.
	Power_Flag = 2; VESC boot-up completed.
	Power_Flag = 3; VESC powered off, the board is powered by the charger.
*/
uint8_t Power_Flag = 0;
/*
	Charge_Flag = 0; Just powered on.
	Charge_Flag = 1; Ready for charging.
	Charge_Flag = 2; Charging in progress.
	Charge_Flag = 3; Battery fully charged.
*/
uint8_t Charge_Flag = 0;
/*
	VESC_Boot_Flag = 0; VESC powered off.
	VESC_Boot_Flag = 1; VESC powered on.
*/
//uint8_t VESC_Boot_Flag = 0;
/*
	Flashlight_Flag = 0; Just powered on.
	Flashlight_Flag = 1; VESC booting up.
	Flashlight_Flag = 2; Front light white, rear light red (forward).
	Flashlight_Flag = 3; Front light red, rear light white (reverse).
	Flashlight_Flag = 4; Brightness set to 10%.
*/
uint8_t Flashlight_Flag = 0;
/*
	Brightness_Flag = 0; Just powered on.
	Brightness_Flag = 1; Starting brightness adjustment.
	Brightness_Flag = 2; Brightness adjustment completed.
*/
uint8_t Brightness_Flag = 0;
/*
	Lightbar_Mode_Flag = 0; Just powered on.
	Lightbar_Mode_Flag = 1; Display battery level.
	Lightbar_Mode_Flag = 2; Do not display battery level.
*/
uint8_t Lightbar_Mode_Flag = 0;
/* 
	Footpad_Activation_Flag = 0; Just powered on.
	Footpad_Activation_Flag = 1; Left 5 LEDs blue, Right 5 LEDs off (adc1 > 2.5V, adc2 < 2.5V).
	Footpad_Activation_Flag = 2; Left 5 LEDs off, Right 5 LEDs blue (adc1 < 2.5V, adc2 > 2.5V).
	Footpad_Activation_Flag = 3; All 10 LEDs blue (adc1 > 2.5V, adc2 > 2.5V).
	Footpad_Activation_Flag = 4; All 10 LEDs off.
*/
uint8_t Footpad_Activation_Flag = 0;
/*
	Power_Display_Flag = 0; Just powered on.
	Power_Display_Flag = 1; 4.08V~4.2V: 10 white LEDs.
	Power_Display_Flag = 2; 4.05V~4.08V: 9 white LEDs.
	Power_Display_Flag = 3; 3.96V~4.05V: 8 white LEDs.
	Power_Display_Flag = 4; 3.87V~3.96V: 7 white LEDs.
	Power_Display_Flag = 5; 3.78V~3.87V: 7 white LEDs.
	Power_Display_Flag = 6; 3.70V~3.78V: 5 white LEDs.
	Power_Display_Flag = 7; 3.62V~3.70V: 4 white LEDs.
	Power_Display_Flag = 8; 3.50V~3.62V: 3 white LEDs.
	Power_Display_Flag = 9; 3.35V~3.50V: 2 red LEDs.
	Power_Display_Flag = 10; 2.80V~3.35V: 1 red LED.
*/
uint8_t Power_Display_Flag = 0;
/*
	Buzzer_Flag = 0; Just powered on.
	Buzzer_Flag = 1; Buzzer is not sounding.
	Buzzer_Flag = 2; Buzzer is sounding.
*/
uint8_t Buzzer_Flag = 0;
/*
	Usart_Flag = 0; Just powered on.
	Usart_Flag = 1; Parsing successful.
	Usart_Flag = 2; Parsing failed or waiting for the next parsing.
*/
uint8_t Usart_Flag = 0;

/*
	VESC boot time.
*/
uint16_t VESC_Boot_Time = 0;

/*
	Buzzer sounding time.
*/
uint16_t Buzzer_Time = 0;
/*
	Charging time.
*/
uint16_t Charge_Time = 0;
/*
	Flashlight time.
*/
uint16_t Flashlight_Time = 0;
/*
	Power on time.
*/
uint16_t Power_Time = 0;
/*
	USART communication time.
*/
uint16_t Usart_Time = 0;
/*
	ADC sampling time.
*/
uint16_t ADC_Time = 0;
/*
	Shutdown time in seconds.
*/
uint16_t Shutdown_Time_S = 0;
/*
	Shutdown time in minutes.
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

///Configured cell type (gets read from EEPROM)
uint8_t Config_Cell_Type = 0;

///Configured boot animation (gets read from EEPROM)
uint8_t Config_Boot_Animation = 0;

///Configured buzzer (gets read from EEPROM)
uint8_t Config_Buzzer = 0;

uint8_t WS2812_Measure = 0;		//Lightbar runtime brightness setting (0-255)

uint16_t Main_Brightness = 0;  //Main lights runtime brightness setting (0-9999) -> 9999 = 0% brightness and 0 = 100% brightness
/*
	Buzzer frequency in BPM, beats per minute, ranging from 60 to 180, corresponding to a duty cycle of 70 to 100)
*/
uint8_t Buzzer_Frequency = 0;
/*
	When the button is double-clicked without pressing it, the headlight stays on for 3 seconds.
*/
uint16_t Flashlight_Detection_Time = 0;
/*
	Charging current and voltage original valuesֵ
*/
float Charge_Current = 0;
/*
	V_I = 0: Sampling charging current.
	V_I = 1: Sampling charging voltage.
*/
uint8_t V_I = 1;
/*
	Number of times the current reaches the shutdown value.
*/
uint8_t Shutdown_Cnt = 0;
/*
	Charger detection time.
*/
uint16_t Charger_Detection_1ms = 0;

