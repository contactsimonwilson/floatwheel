/**
  ******************************************************************************
  * @file       ： main.c
  * @author     :  FCZ
  * @version    ： V1.1.6
  * @date       ： 2022年03月28日
  * @brief      ： 主函数 - LCM灯控
  * @mcu        :  HK32F030MF4P6
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2022-03-28 V1.0.0:初始版本
  2022-05-16 增加开机显示进度条和充电显示电压
  2022-05-17 更改充电显示为呼吸灯效果
  2022-06-09 关机时间由5分钟改为15分钟 
             占空比由超过70%改为超过80%蜂鸣器“哔”“哔”的响
			 自动关机条件由原来的不踩脚踏板增加一条且转速低于1000才开始计时关机
  2022-07-19 电池由12串改为20串
             关机时间改为30分钟
			 充电器电压检测加平均值滤波，电压判断加回执电压范围
  2023-01-16 WS2812驱动由硬件SPI模拟改为IO口加延时模拟
  2023-02-05 增加档位
			 一档 大灯最暗 WS2812最亮 蜂鸣器响一声
			 二档 大灯中档 WS2812中档 蜂鸣器响两声
			 三档 大灯最亮 WS2812最暗 蜂鸣器响三声
  2023-12-25 增加四挡
			 四档 大灯关闭 WS2812关闭 蜂鸣器响四声
			 WS2812开机进度条速度增快一倍
  ----------------------------------------------------------------------------*/
#include "hk32f030m.h"
#include "led.h"
#include "time.h"
#include "spi.h"
#include "ws2812.h"
#include "power.h"
#include "key.h"
#include "usart.h"
#include "adc.h"
#include "buzzer.h"
#include "led_pwm.h"
#include "test.h"
#include "task.h"
#include "io_ws2812.h"
#include "iwdg.h"

//RCC_ClocksTypeDef RCC_Clock;

/*
										
*/

uint16_t PWM_Val;

#define IWDG_DEBUG	1
/**************************************************
 * @brie   :main()
 * @note   :主函数
 * @param  :无
 * @retval :无
 **************************************************/
int main(void)
{	
	//RCC_GetClocksFreq(&RCC_Clock);
	
	LED_Init();
	Buzzer_Init();
	ADC1_Init();
	Time6_Init();
	WS2812_Init();
	Power_On_Delay_1ms = 0;
	while(Power_On_Delay_1ms < 500);

	Power_Init();
	KEY_Init();
	USART1_Init(115200);
	LED_PWM_Init();

#if IWDG_DEBUG
	IWDG_Init();
#endif	
	KEY1_State = 1;
	
	Charge_Voltage = 3.3;
	Power_Time = 0;
	
	while(1)
	{
		LED_Task();
		KEY1_Task();
		WS2812_Task();
		Power_Task();
//		Charge_Task();
		Flashlight_Task();
		Flashlight_Detection();
		Buzzer_Task();
		Usart_Task();
		ADC_Task();
		Conditional_Judgment();
		IWDG_ReloadCounter();  
	}
}

