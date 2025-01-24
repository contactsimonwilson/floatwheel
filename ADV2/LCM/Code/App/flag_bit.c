#include "flag_bit.h"

/*
	Power_Flag = 0; 刚上电
	Power_Flag = 1；VESC开机
	Power_Flag = 2; VESC开机完成
	Power_Flag = 3; VESC关机，充电器给板子供电
*/
uint8_t Power_Flag = 0;
/*
	Charge_Flag = 0; 刚上电
	Charge_Flag = 1；准备充电
	Charge_Flag = 2；充电打开
	Charge_Flag = 3；电池电充满了
*/
uint8_t Charge_Flag = 0;
///*
//	VESC_Boot_Flag = 0; VESC关机
//	VESC_Boot_Flag = 1；VESC开机
//*/
//uint8_t VESC_Boot_Flag = 0;
/*
	Flashlight_Flag = 0; 刚上电
	Flashlight_Flag = 1; VESC开机
	Flashlight_Flag = 2；VESC前面白灯后面红灯(正转)
	Flashlight_Flag = 3；VESC前面红灯后面白灯(反转)
	Flashlight_Flag = 4; 亮度10%
*/
uint8_t Flashlight_Flag = 0;
/*
	Brightness_Flag = 0; 刚上电
	Brightness_Flag = 1; 开始调整亮度
	Brightness_Flag = 2；亮度调整完成
*/
uint8_t Brightness_Flag = 0;
/*
	WS2812_Display_Flag = 0; 刚上电
	WS2812_Display_Flag = 1；显示电量
	WS2812_Display_Flag = 2；不显示电量
*/
uint8_t WS2812_Display_Flag = 0;
/*
	WS2812_Flag = 0; 刚上电
	WS2812_Flag = 1；左侧5个蓝灯     右侧5个灯不发光   adc1>2.5V  adc2<2.5V
	WS2812_Flag = 2；左侧5个灯不发光 右侧5个蓝灯       adc1<2.5V  adc2>2.5V
	WS2812_Flag = 3；10个灯都量蓝灯                    adc1>2.5V  adc2>2.5V
	WS2812_Flag = 4；10个灯都灭
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
	VESC开机时间
*/
uint16_t VESC_Boot_Time = 0;

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
	ADC采样时间
*/
uint16_t ADC_Time = 0;
/*
	关机时间 秒
*/
uint16_t Shutdown_Time_S = 0;
/*
	关机时间 分钟
*/
uint8_t Shutdown_Time_M = 0;
/*
	电池电压
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
	转速
*/
//long VESC_Rpm = 0;
/*
	母线电流
*/
//float AvgInputCurrent = 0;
/*
	占空比
*/
//float DutyCycleNow = 0;
/*
	充电口电压
*/
float Charge_Voltage = 0;
/*
	Gear_Position = 0 刚开机
	Gear_Position = 1 大灯最暗 WS2812最亮 蜂鸣器响一声
	Gear_Position = 2 大灯中档 WS2812中档 蜂鸣器响两声
	Gear_Position = 3 大灯最亮 WS2812最暗 蜂鸣器响三声
	Gear_Position = 4 大灯关闭 WS2812关闭 蜂鸣器响四声
*/
uint8_t Gear_Position = 0;
/*
	WS2812量度
*/
uint8_t WS2812_Measure = 0;
/*
	蜂鸣器 bpm 60-180 对应占空比 70-100
*/
uint8_t Buzzer_Frequency = 0;
/*
	按键双击脚踏板没踩下 大灯亮3S
*/
uint16_t Flashlight_Detection_Time = 0;
/*
	充电电压和充电的电流的原始值
*/
float Charge_Current = 0;
/*
	0 采样充电电流
	1 采样充电电压
*/
uint8_t V_I = 1;
/*
	电流达到关机的次数
*/
uint8_t Shutdown_Cnt = 0;
/*
	充电器检测时间
*/
uint16_t Charger_Detection_1ms = 0;
/*
	开机延时
*/
uint16_t Power_On_Delay_1ms = 0;

