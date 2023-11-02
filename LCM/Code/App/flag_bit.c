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
        Lightbar_Mode_Flag = 0; Just powered on.
        Lightbar_Mode_Flag = 1; Display battery level.
        Lightbar_Mode_Flag = 2; Do not display battery level.
*/
uint8_t WS2812_Display_Flag = 0;
/*
        Footpad_Activation_Flag = 0; Just powered on.
        Footpad_Activation_Flag = 1; Left 5 LEDs blue, Right 5 LEDs off (adc1 > 2.5V, adc2 < 2.5V).
        Footpad_Activation_Flag = 2; Left 5 LEDs off, Right 5 LEDs blue (adc1 < 2.5V, adc2 > 2.5V).
        Footpad_Activation_Flag = 3; All 10 LEDs blue (adc1 > 2.5V, adc2 > 2.5V).
        Footpad_Activation_Flag = 4; All 10 LEDs off.
        Footpad_Activation_Flag = 5; Flywheel mode, pattern
*/
uint8_t WS2812_Flag = 0;
/*
	Power_Display_Flag = 0; 刚上电
	Power_Display_Flag = 1； 4.08V~4.2V 	10个白灯
	Power_Display_Flag = 2； 4.05V~4.08V 9个白灯
	Power_Display_Flag = 3； 3.96V~4.05V 8个白灯
	Power_Display_Flag = 4； 3.87V~3.96V 7个白灯
	Power_Display_Flag = 5； 3.78V~3.87V 7个白灯
	Power_Display_Flag = 6； 3.70V~3.78V 5个白灯
	Power_Display_Flag = 7； 3.62V~3.70V 4个白灯
	Power_Display_Flag = 8； 3.50V~3.62V 3个白灯
	Power_Display_Flag = 9； 3.35V~3.50V 2个红灯
	Power_Display_Flag = 10; 2.80V~3.35V 1个红灯
*/
uint8_t Power_Display_Flag = 0;
/*
	Buzzer_Flag = 0; 刚上电
	Buzzer_Flag = 1；蜂鸣器不响
	Buzzer_Flag = 2；蜂鸣器响
*/
uint8_t Buzzer_Flag = 0;
/*
	Usart_Flag = 0; 刚上电
	Usart_Flag = 1；解析成功
	Usart_Flag = 2；解析失败或等待下一次解析
*/
uint8_t Usart_Flag = 0;

/*
	蜂鸣器响的时间
*/
uint16_t Buzzer_Time = 0;
/*
	充电计时
*/
uint16_t Charge_Time = 0;
/*
	照明灯
*/
uint16_t Flashlight_Time = 0;
/*
	开机时间
*/
uint16_t Power_Time = 0;
/*
	串口通信
*/
uint16_t Usart_Time = 0;
/*
	ADC sampling time.
*/
uint16_t ADC_Time = 0;
/*
	Shutdown counter, milliseconds and minutes
*/
uint16_t Shutdown_Time_S = 0;
uint8_t Shutdown_Time_M = 0;
/*
	ADC1
*/
float ADC1_Val = 0;
/*
	ADC2
*/
float ADC2_Val = 0;
/*
	Charging Port Voltage
*/
float Charge_Voltage = 0;
/*
	Light_Profile = 0 Just powered on.
	Light_Profile = 1 Headlight bightness low, Lightpad brightness high, beep once
	Light_Profile = 2 Headlight bightness mid, Lightpad brightness mid, beep twice
	Light_Profile = 3 Headlight bightness high, Lightpad brightness low, beep thrice
*/
uint8_t Gear_Position = 0;
/*
	WS2812量度
*/
uint8_t WS2812_Measure = 0;
/*
	 Buzzer frequency in BPM, beats per minute, ranging from 60 to 180, corresponding to a duty cycle of 70 to 100)
*/
uint8_t Buzzer_Frequency = 0;
/*
	 When the button is double-clicked without pressing it, the headlight stays on for 3 seconds.
*/
uint16_t Flashlight_Detection_Time = 0;
/*
	Charging current and voltage original values
*/
float Charge_Current = 0;
/*
	V_I = 0: Sampling charging current.
	V_I = 1: Sampling charging voltage.
*/
uint8_t V_I = 1;
/*
	电流达到关机的次数
*/
uint8_t Shutdown_Cnt = 0;
/*
	Charger detection time.
*/
uint16_t Charger_Detection_1ms = 0;

