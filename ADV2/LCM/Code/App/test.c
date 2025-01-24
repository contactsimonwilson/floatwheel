#include "test.h"


/*以下代码都是测试相关部分功能的*/
uint8_t  Test_Step = 0;
uint16_t Test_Counter = 0;

/**************************************************
 * @brie   :Test_Charge()
 * @note   :测试充电口
 * @param  :无
 * @retval :无
 **************************************************/
void Test_Charge(void)
{
	static uint8_t test_charge = 0;
	uint16_t adc_val = 0;
	float charge_voltage = 0;
	
	switch(test_charge)
	{
		case 0:
			adc_val = Read_ADC_Value(3);
			charge_voltage = (float)(adc_val*0.0257080078125);
			if(charge_voltage > 1.5)  //充电器插入
			{
				Test_Counter = 0;
				test_charge = 1;
			}
		break;
		
		case 1:
			if(Test_Counter >= 1000) //延时1S
			{
				adc_val = Read_ADC_Value(3);
				charge_voltage = (float)(adc_val*0.0257080078125);
				if(charge_voltage > 1.5) //充电器确实插入
				{
					//CHARGE_ON;   //打开充电口
					test_charge = 2;
				}
				else
				{
					//CHARGE_OFF;  //关闭充电口
					test_charge = 0;
				}
			}
		break;
			
		case 2:	
			adc_val = Read_ADC_Value(3);
			charge_voltage = (float)(adc_val*0.0257080078125);
			if(charge_voltage < 1.0)  //充电器拔出
			{
				//CHARGE_OFF;  //关闭充电口
				test_charge = 0;
			}
		break;
	}
}

/**************************************************
 * @brie   :Test_LED()
 * @note   :测试LED
 * @param  :无
 * @retval :无
 **************************************************/
void Test_LED(void)
{
	static uint8_t  test_led = 0;
	static uint8_t  led_b_f = 0;
	static uint16_t led_pwm = 0;
	static uint8_t  pwm_st =0;
	static uint8_t  pwm_cnt =0;
	
	switch(test_led)
	{
		case 0:
			if(led_b_f == 0)
			{
				led_b_f = 1;
				LED_F_OFF;
				LED_B_ON;
			}
			else
			{
				led_b_f = 0;
				LED_B_OFF;
				LED_F_ON;
			}
			test_led = 1;
		break;
			
		case 1:
			if(Test_Counter > 10)
			{
				Test_Counter = 0;
				switch(pwm_st)
				{
					case 0:
						led_pwm += 500;
						if(led_pwm >= 5000)
						{
							led_pwm -= 1;
							pwm_st = 1;
						}
					break;
					
					case 1:
						led_pwm += 1;
						pwm_st = 2;
					case 2:
						led_pwm -= 500;
						if(led_pwm == 0)
						{
							pwm_st = 0;
						}
					break;	
				}
					
				TIM_SetCompare2(TIM1,9000);
				pwm_cnt++;
				
				if(pwm_cnt >= 20)
				{
					pwm_cnt = 0;
					led_pwm = 0;
					pwm_st = 0;
					test_led = 0;
					TIM_SetCompare2(TIM1,0);
				}
			}
		break;	
	}
}

/**************************************************
 * @brie   :Test_USART()
 * @note   :测试串口
 * @param  :无
 * @retval :无
 **************************************************/
void Test_USART(void)
{
	static uint8_t  test_usart = 0;
	uint8_t result;
	
	switch(test_usart)
	{
		case 0:
			Get_Vesc_Pack_Data(COMM_GET_VALUES);
			test_usart = 1;
		break;
		
		case 1:
			if(VESC_RX_Flag == 1)
			{
				VESC_RX_Flag = 0;
				result = Protocol_Parse(VESC_RX_Buff);
				
				if(result == 0) //解析成功
				{
					//Buzzer_Ring(200);		
				}
				else	//解析失败
				{
					//Buzzer_Ring(1000);
				}
				Test_Counter = 0;
				test_usart = 2;
			}
			else
			{
				test_usart = 3;
				Test_Counter = 0;
			}
		break;
			
		case 2:
			if(Test_Counter >= 500)
			{
				test_usart = 0;
			}				
		break;
			
		case 3:
			
			if(VESC_RX_Flag == 1)
			{
				test_usart = 1;
			}
			else if(Test_Counter >= 500)
			{
				test_usart = 0;
			}
		break;
				
	}
}

float adc1_voltage = 0;
float adc2_voltage = 0;
float charge_voltage = 0;
/**************************************************
 * @brie   :Test_ADC()
 * @note   :测试ADC
 * @param  :无
 * @retval :无
 **************************************************/
void Test_ADC(void)
{
	static uint8_t  test_adc = 0;
	uint16_t adc_val = 0;
	
	switch(test_adc)
	{
		case 0:
			adc_val = Read_ADC_Value(1);
		  adc1_voltage = adc_val*0.0012890625;

			adc_val = Read_ADC_Value(2);
		  adc2_voltage = adc_val*0.0012890625;

			adc_val = Read_ADC_Value(3);
			charge_voltage = (float)(adc_val*0.0257080078125);
		
			Test_Counter = 0;
			test_adc = 1;
		break;	

		case 1:
			if(Test_Counter>1000)
			{
				test_adc = 0;
			}
		break;
		
		case 2:
			adc_val = Read_ADC_Value(2);
		    adc2_voltage = adc_val*0.0008056640625;
		
			Test_Counter = 0;
			test_adc = 3;
		break;
		
		case 3:
			if(Test_Counter>100)
			{
				test_adc = 4;
			}
		break;
			
		case 4:
			adc_val = Read_ADC_Value(3);
			charge_voltage = (float)(adc_val*0.0257080078125);
		
			Test_Counter = 0;
			test_adc = 5;
		break;

		case 5:
			if(Test_Counter>100)
			{
				test_adc = 0;
			}
		break;			
	}
}

/**************************************************
 * @brie   :Test_Task()
 * @note   :测试任务
 * @param  :无
 * @retval :无
 **************************************************/
void Test_Task(void)
{
	switch(Test_Step)
	{
		case 0:
			
		break;
		
		case 1: //测试充电口
			Test_Charge();
		break;
				
		case 2: //测试LED
			Test_LED();
		break;
						
		case 3: //测试串口
			Test_USART();
		break;
		
		case 4: //测试ADC1 ADC2
			Test_ADC();
		break;
		
	}
}

