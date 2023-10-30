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

//RCC_ClocksTypeDef RCC_Clock;

/*
										
*/

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
	WS2812_Init();
	Power_Init();
	KEY_Init();
	USART1_Init(115200);
	LED_PWM_Init();
	Time6_Init();
	if(KEY1 ==  0)
	{
		KEY1_State = 1;
	}
	while(1)
	{
		KEY1_Task();
		WS2812_Task();
		Power_Task();
		Charge_Task();
		Headlights_Task();
		Buzzer_Task();
		Usart_Task();
		ADC_Task();
		Conditional_Judgment();
	}
}

