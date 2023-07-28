#include "task.h"

/**************************************************
 * @brie   :LED_Task()
 * @note   :LED���� 
 * @param  :��
 * @retval :��
 **************************************************/
void LED_Task(void)
{
//	if(LED_Counter >= LED_Filp_Time)
//	{
//		LED_Counter = 0;
//		LED1_FILP;
//	}
}

/**************************************************
 * @brie   :KEY1_Task()
 * @note   :KEY1����
 * @param  :��
 * @retval :��
 **************************************************/
void KEY1_Task(void)
{
	if(KEY1_State == 0 || Power_Flag == 3)  //��������簴����������
	{
		return;
	}
	
	switch(KEY1_State)
	{
		case 1:  	//����
			if(Power_Flag != 2)
			{
				Power_Flag = 1;  //VESC����
			}	
		break;
		
		case 2:		//˫��	
			if(Power_Flag == 2) //�������
			{
				Gear_Position++;
				if(Gear_Position == 4)
				{
					Gear_Position = 1;
				}
				
			}
		break;
		
		case 3:		//����
			Power_Flag = 3;  //VESC�ػ�
			Flashlight_Flag = 0;
			WS2812_Display_Flag =0;
		break;
		
		case 4:		//����
			if(Power_Flag == 2) //�������
			{
				if(Buzzer_Flag == 2)
				{
					Buzzer_Flag = 1;
				}
				else
				{
					Buzzer_Flag = 2;
				}
			}
		break;
		
	}
	KEY1_State = 0;
}

/**************************************************
 * @brie   :Power_Display()
 * @note   :������ʾ
 * @param  :��
 * @retval :��
 **************************************************/
void Power_Display(void)
{
	uint8_t i;
	uint8_t num;
	
	switch(Power_Display_Flag)
	{
		case 1://4.08V~4.2V 	10���׵�
			num = 10;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,WS2812_Measure,WS2812_Measure,WS2812_Measure);
			}
		break;
		
		case 2://4.05V~4.08V 9���׵�
			num = 9;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,WS2812_Measure,WS2812_Measure,WS2812_Measure);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 3://3.96V~4.05V 8���׵�
			num = 8;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,WS2812_Measure,WS2812_Measure,WS2812_Measure);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 4://3.87V~3.96V 7���׵�
			num = 7;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,WS2812_Measure,WS2812_Measure,WS2812_Measure);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 5://3.78V~3.87V 6���׵�
			num = 6;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,WS2812_Measure,WS2812_Measure,WS2812_Measure);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 6://3.70V~3.78V 5���׵�
			num = 5;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,WS2812_Measure,WS2812_Measure,WS2812_Measure);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 7://3.62V~3.70V 4���׵�
			num = 4;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,WS2812_Measure,WS2812_Measure,WS2812_Measure);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 8://3.50V~3.62V 3���׵�
			num = 3;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,WS2812_Measure,WS2812_Measure,WS2812_Measure);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 9://3.35V~3.50V 2�����
			num = 2;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,0,WS2812_Measure,0);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 10://2.80V~3.35V 1�����
			num = 1;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,0,WS2812_Measure,0);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		default:
			for(i=0;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
	}
	WS2812_Refresh();//ˢ����ʾ
}

/**************************************************
 * @brie   :WS2812()
 * @note   :����ʾ����WS2812
 * @param  :��
 * @retval :��
 **************************************************/
void WS2812(void)
{
	uint8_t i;
	
	switch(WS2812_Flag)
	{
		case 1://���5������     �Ҳ�5���Ʋ�����   adc1>2.5V  adc2<2.5V
			for(i=0;i<5;i++)
			{
				WS2812_Set_Colour(i,0,0,WS2812_Measure);
			}
				for(i=5;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 2://���5���Ʋ����� �Ҳ�5������       adc1<2.5V  adc2>2.5V
			for(i=0;i<5;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
				for(i=5;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,WS2812_Measure);
			}
		break;
		
		case 3://10���ƶ�������                    adc1>2.5V  adc2>2.5V
			for(i=0;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,WS2812_Measure);
			}
		break;
			
		case 4://�ر�10���� 
			for(i=0;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		default:
			for(i=0;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
	}
	WS2812_Refresh();//ˢ����ʾ
}


/**************************************************
 * @brie   :WS2812_Boot()
 * @note   :��ʾ����
 * @param  :��
 * @retval :��
 **************************************************/
void WS2812_Boot(void)
{
	uint8_t i;
	uint8_t num;
	
	if(Power_Time <= 500)
	{
		num = 1;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}
	}
	else if(Power_Time <= 1000)
	{
		num = 2;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}	
	}
	else if(Power_Time <= 1500)
	{
		num = 3;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}
	}
	else if(Power_Time <= 2000)
	{
		num = 4;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}
	}
	else if(Power_Time <= 2500)
	{
		num = 5;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}
	}
	else if(Power_Time <= 3000)
	{
		num = 6;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}
	}
	else if(Power_Time <= 3500)
	{
		num = 7;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}
	}
	else if(Power_Time <= 4000)
	{
		num = 8;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}
	}
	else if(Power_Time <= 4500)
	{
		num = 9;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}
	}
	else 
	{
		num = 10;
		for(i=0;i<num;i++)
		{
			WS2812_Set_Colour(i,255,0,255);
		}
		for(i=num;i<10;i++)
		{
			WS2812_Set_Colour(i,0,0,0);
		}
	}
	WS2812_Refresh();//ˢ����ʾ
}




uint8_t brightness = 1;
/**************************************************
 * @brie   :WS2812_Cal_Bri()
 * @note   :��������
 * @param  :���� 1�α�ʾ200ms
 * @retval :����
 **************************************************/
uint8_t WS2812_Cal_Bri(uint8_t cnt)
{
	
	
	if(cnt < 50)
	{
		brightness++;
	}
	else
	{
		brightness--;
	}
	
	if(brightness < 1)
	{
		brightness = 1;
	}
	
	if(brightness > 50)
	{
		brightness = 50;
	}
	
//	if(cnt == 50)
//	{
//	brightness = brightness;
//	}
//	
//	if(cnt == 99)
//	{
//	brightness = brightness;
//	}
//	switch(cnt)
//	{
//		case 0:
//			brightness = 0x03;
//		break;
//		
//		case 1:
//			brightness = 0x04;
//		break;
//		
//		case 2:
//			brightness = 0x05;
//		break;
//		
//		case 3:
//			brightness = 0x06;
//		break;
//		
//		case 4:
//			brightness = 0x07;
//		break;
//		
//		case 5:
//			brightness = 0x08;
//		break;
//		
//		case 6:
//			brightness = 0x07;
//		break;
//		
//		case 7:
//			brightness = 0x06;
//		break;
//		
//		case 8:
//			brightness = 0x05;
//		break;
//		
//		case 9:
//			brightness = 0x04;
//		break;
//		
//		case 10:
//			brightness = 0x03;
//		break;
//	}
	
	return brightness;
}

/**************************************************
 * @brie   :WS2812_Charge()
 * @note   :��ʾ���
 * @param  :��
 * @retval :��
 **************************************************/
void WS2812_Charge(void)
{
	uint8_t i;
	uint8_t num;
	static uint8_t cnt = 0;
	uint8_t brightness = 0;
	
	brightness = WS2812_Cal_Bri(cnt);
	switch(Power_Display_Flag)
	{
		case 1://4.08V~4.2V 	10���׵�
			
			num = 10;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,brightness,brightness,brightness);
			}
		break;
		
		case 2://4.05V~4.08V 9���׵�
			num = 9;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,brightness,brightness,brightness);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 3://3.96V~4.05V 8���׵�
			num = 8;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,brightness,brightness,brightness);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 4://3.87V~3.96V 7���׵�
			num = 7;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,brightness,brightness,brightness);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 5://3.78V~3.87V 6���׵�
			num = 6;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,brightness,brightness,brightness);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 6://3.70V~3.78V 5���׵�
			num = 5;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,brightness,brightness,brightness);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 7://3.62V~3.70V 4���׵�
			num = 4;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,brightness,brightness,brightness);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 8://3.50V~3.62V 3���׵�
			num = 3;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,brightness,brightness,brightness);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 9://3.35V~3.50V 2�����
			num = 2;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,0,brightness,0);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 10://2.80V~3.35V 1�����
			num = 1;
			for(i=0;i<num;i++)
			{
				WS2812_Set_Colour(i,0,brightness,0);
			}
			for(i=num;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		default:
			for(i=0;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
	}
	
	cnt++;
	
	if(cnt == 100)
	{
		cnt = 0;
	}
	
	WS2812_Refresh();//ˢ����ʾ
}	

/**************************************************
 * @brie   :WS2812_Task()
 * @note   :WS2812���� 
 * @param  :��
 * @retval :��
 **************************************************/
void WS2812_Task(void)
{
//	static uint8_t ws2812_flag_last = 0; //��һ�ε�״̬
//	static uint8_t power_display_flag_last = 0; //��һ�ε�״̬
	uint8_t i;

	if(WS2812_Counter < 20) //20msˢ��һ��
	{
		return;
	}
	WS2812_Counter = 0;
	
	if(Power_Flag == 0 || (Power_Flag == 3 && Charge_Flag == 0))
	{
			for(i=0;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
			WS2812_Refresh();//ˢ����ʾ
			
			WS2812_Display_Flag = 0;
			WS2812_Flag = 0;
			Power_Display_Flag = 0;
			
			return;
	}
	
	if(Power_Flag == 1)
	{
		WS2812_Boot();  //��������
		return;
	}
	
	if(Charge_Flag == 3) //��ص������
	{
		for(i=0;i<10;i++)
		{
			WS2812_Set_Colour(i,255,255,255);
		}
		return;
	}
	
	if(Charge_Flag == 2) //��������ʾ
	{
		WS2812_Charge();
		return;
	}
	
	switch(Gear_Position)
	{
		case 1: //1��
			WS2812_Measure = WS2812_1_BRIGHTNESS;
		break;
		
		case 2:	//2��
			WS2812_Measure = WS2812_2_BRIGHTNESS;
		break;
		
		case 3: //3��
			WS2812_Measure = WS2812_3_BRIGHTNESS;
		break;
		
		default:
			
		break;
	}
	
	if(WS2812_Display_Flag == 1)  //��ʾ����
	{
//		if(Power_Display_Flag == power_display_flag_last) //��һ�κ���һ��һ��ֱ���˳�
//		{
//			return;
//		}
//		else
//		{
//			power_display_flag_last = Power_Display_Flag;
//			Power_Display();// ������ʾ
//		}
		Power_Display();// ������ʾ
	}
	else //����ʾ����
	{
//		if(ws2812_flag_last == WS2812_Flag) //��һ�κ���һ��һ��ֱ���˳�
//		{
//			return;
//		}
//		else
//		{
//			ws2812_flag_last = WS2812_Flag;
//			WS2812();//����ʾ����WS2812
//		}
		WS2812();//����ʾ����WS2812
	}
	
}

/**************************************************
 * @brie   :Power_Task()
 * @note   :��Դ���� 
 * @param  :��
 * @retval :��
 **************************************************/
void Power_Task(void)
{
	static uint8_t power_flag_last = 0; //��һ�ε�״̬
	static uint8_t power_step = 0;
	
	if(power_flag_last == Power_Flag && Power_Flag != 1)
	{
		return;
	}
	power_flag_last = Power_Flag;
	
	switch(Power_Flag)
	{
		case 1://VESC����
			PWR_ON;
			Flashlight_Flag = 1;
			switch(power_step)
			{
				case 0:
					Power_Time = 0;
					power_step = 1;
				break;
				
				case 1:
					if(Power_Time > VESC_BOOT_TIME)
					{
						Power_Flag = 2; //�������
						Gear_Position = 1; //������Ĭ����1��
						Buzzer_Flag = 2;    //����Ĭ�Ϸ�������
						power_step = 0;
					}
				break;
			}
			
		break;	
		
		case 3://VESC�ػ�������������ӹ���
			PWR_OFF;
			//LED1_Filp_Time(1000);	
			//Charge_Flag = 1; //׼�����
		break;
		
		default:
			
		break;
	}
}

/**************************************************
 * @brie   :Charge_Task()
 * @note   :������� 
 * @param  :��
 * @retval :��
 **************************************************/
void Charge_Task(void)
{
	static uint8_t charge_step = 0; 
		
	if(Charge_Flag == 0)
	{
		return;
	}
	
	switch(charge_step)
	{
		case 0:
			Charge_Time = 0;
			charge_step = 1;
		break;
		
		case 1:
			if(Charge_Time > 1000)  //��ʱ1S
			{
				charge_step = 2;
			}
		break;
		
		case 2:
			CHARGE_ON;  //�򿪳����
			Charge_Flag = 2;
		    charge_step = 3;
		break;
		
		case 3:
			Charge_Time = 0;
			charge_step = 4;
		break;
			
		case 4:	
			if(Charge_Time > DETECTION_SWITCH_TIME) 
			{
				V_I = 1;
				Charge_Time = 0;
				LED1_ON; //�ɼ�����ѹ
				charge_step = 5;
			}
		break;
			
		case 5:
			if(Charge_Time > DETECTION_SWITCH_TIME) 
			{
				V_I = 0;
				Charge_Time = 0;
				LED1_OFF; //�ɼ������
				charge_step = 4;
			}		
		break;
			
		
		default:
			
		break;
		
	}
}

uint8_t val = 0;
uint8_t flashlight_flag_last_2 = 0;
/**************************************************
 * @brie   :Flashlight_Bright()
 * @note   :����������
 * @param  :red_white = 1 ǰ�����ư� �������ƺ�
 *          red_white = 2 ǰ�����ƺ� �������ư�
 *          bright = 1    ���ȴ�0% -10% 2��
 *          bright = 2    ���ȴ�10%-100% 2��
 * @retval :��
 **************************************************/
void Flashlight_Bright(uint8_t red_white,uint8_t bright)
{
	static uint8_t flashlight_bright_step = 0;
	uint16_t brightness = 0;

	
	if(flashlight_flag_last_2 != Flashlight_Flag)
	{
		flashlight_bright_step = 0;
		flashlight_flag_last_2 = Flashlight_Flag;
	}
	
	if(Flashlight_Flag == 4)
	{
		TIM_SetCompare2(TIM1,9000);//��10%��ʼ
		return;
	}
	
	switch(flashlight_bright_step)
	{
		case 0:
				if(red_white == 1)
				{
					LED_F_OFF;
					LED_B_ON;
					val = 1;
				}
				else
				{
					LED_B_OFF;
					LED_F_ON;
					val = 2;
				}
				flashlight_bright_step = 1;
		break;
				
		case 1:
				Flashlight_Time = 0;
				flashlight_bright_step = 2;
		break;
		
		case 2:
			if(bright == 1)
			{
				TIM_SetCompare2(TIM1,9999); //��0%��ʼ
				flashlight_bright_step = 3;
			}
			else
			{
				TIM_SetCompare2(TIM1,9000);//��10%��ʼ
				flashlight_bright_step = 4;
			}
		break;
		
		case 3://���ȴ�0% -10% 2��
			if(Flashlight_Time%2 == 0)
			{
				brightness = Flashlight_Time/2;
				brightness = 9999-brightness+1;
				TIM_SetCompare2(TIM1,brightness);
			}
			if(Flashlight_Time >= 2000)
			{
				TIM_SetCompare2(TIM1,9000);
				flashlight_bright_step = 5;
			}
		break;
		
		case 4://���ȴ�10%-100% 2��
		
			if(Flashlight_Time%2 == 0)
			{
				switch(Gear_Position)
				{
					case 1:
						brightness = (Flashlight_Time*1.0F)+1000;
						brightness = 9999-brightness+1;
					break;
					
					case 2:
						brightness = (Flashlight_Time*2.5F)+1000;
						brightness = 9999-brightness+1;
					break;
					
					case 3:
						brightness = (Flashlight_Time*4.5F)+1000;
						brightness = 9999-brightness+1;
					break;
					
					default:
						
					break;
				}
				
				TIM_SetCompare2(TIM1,brightness);
			}
			if(Flashlight_Time >= 2000)
			{
				switch(Gear_Position)
				{
					case 1:
						TIM_SetCompare2(TIM1,7000);
					break;
					
					case 2:
						TIM_SetCompare2(TIM1,4000);
					break;
					
					case 3:
						TIM_SetCompare2(TIM1,0);
					break;
					
					default:
						
					break;
				}
				
				flashlight_bright_step = 5;
			}
		break;
		
		case 5://���ȵ�����
			Brightness_Flag = 2;
			flashlight_bright_step = 0;
		break;
		
		default:
			
		break;
	}

}
	
/**************************************************
 * @brie   :Flashlight_Task()
 * @note   :���������� 
 * @param  :��
 * @retval :��
 **************************************************/
void Flashlight_Task(void)
{
	static uint8_t flashlight_flag_last = 0;
	
	if(Power_Flag == 3 || Power_Flag == 0) //VESC�ϵ������ƹر�
	{
		LED_B_OFF;
		LED_F_OFF;
		TIM_SetCompare2(TIM1,0);
		return;
	}
	
	if(flashlight_flag_last == Flashlight_Flag && Brightness_Flag == 2) //�����Ѿ�������
	{
		return;
	}
	else if(flashlight_flag_last != Flashlight_Flag)
	{
		flashlight_flag_last = Flashlight_Flag;
		Brightness_Flag = 1;
	}
	
	switch(Flashlight_Flag)
	{
		case 1://VESC���ϵ�ǰ�����������ȴ�0%����2��ﵽ10%
			Flashlight_Bright(1,1);
		break; 
		
		case 2://VESCǰ��׵ƺ�����(��ת)
			Flashlight_Bright(1,2);
		break;
		
		case 3://VESCǰ���ƺ���׵�(��ת)
			Flashlight_Bright(2,2);
		break;
		
		case 4://VESCǰ���ƺ���׵�(��ת)
			Flashlight_Bright(2,2);
			Brightness_Flag = 2;
			val = 3;
		break;
		
		default:
			
		break;
	}
}

void Flashlight_Detection(void)
{
	static uint8_t gear_position_last = 0;
		
	if(gear_position_last == Gear_Position && Flashlight_Detection_Time >= 3100)
	{
		Flashlight_Detection_Time = 3100;
		return;
	}
	else
	{
		if(gear_position_last != Gear_Position)
		{
			if(ADC1_Val < 2.5F && ADC2_Val < 2.5F)
			{
				switch(Gear_Position)
				{
					case 1:
						TIM_SetCompare2(TIM1,7000);
					break;
					
					case 2:
						TIM_SetCompare2(TIM1,4000);
					break;
					
					case 3:
						TIM_SetCompare2(TIM1,0);
					break;
					
					default:
						
					break;	
				}
				Flashlight_Detection_Time = 0;
			}
			else
			{
				switch(Gear_Position)
				{
					case 1:
						TIM_SetCompare2(TIM1,7000);
					break;
					
					case 2:
						TIM_SetCompare2(TIM1,4000);
					break;
					
					case 3:
						TIM_SetCompare2(TIM1,0);
					break;
					
					default:
						
					break;	
				}
				Flashlight_Detection_Time = 3100;
			}
			gear_position_last = Gear_Position;
		}
		else
		{
			if(Flashlight_Detection_Time >= 3000)
			{
				TIM_SetCompare2(TIM1,9000);
				Flashlight_Detection_Time = 3100;
			}
		}
		
	}
}
/**************************************************
 * @brie   :Buzzer_Task()
 * @note   :���������� 
 * @param  :��
 * @retval :��
 **************************************************/
void Buzzer_Task(void)
{
	static uint8_t buzzer_step = 0;
	static uint8_t gear_position_last = 0; //��һ�εĵ�λ
	static uint8_t ring_frequency = 0;
	static uint16_t sound_frequency = 0;
	
	if(Power_Flag != 2 || Buzzer_Flag == 1) //VESC�ϵ��������ر� 
	{
		BUZZER_OFF;
		buzzer_step = 0;
		return;
	}
	
	if(Buzzer_Frequency == 0 && gear_position_last == Gear_Position) //���������Ƶ��Ϊ0����һ�εĵ�λ������εĵ�λ
	{
		BUZZER_OFF;
		buzzer_step = 0;
		return;
	}
	
	if(Buzzer_Frequency != 0)	
	{
		switch(buzzer_step)
		{
			case 0:
				sound_frequency = (uint16_t)(-2.78F*Buzzer_Frequency+666);
				Buzzer_Time = 0;
				buzzer_step = 1;
			break;
			
			case 1:
				Buzzer_Ring(sound_frequency>>2);
				buzzer_step = 2;
			break;
			
			case 2:
				if(Buzzer_Time > sound_frequency)
				{	
					buzzer_step = 0;
				}
			break;
				
			default:
			
		  break;
		}
	}
	else
	{
		switch(buzzer_step)
		{
			case 0:
				Buzzer_Time = 0;
				buzzer_step = 1;
			break;
			
			case 1:
				Buzzer_Ring(200);
				buzzer_step = 2;
			break;
			
			case 2:
				if(Buzzer_Time > 400)
				{	
					ring_frequency++;
					buzzer_step = 0;
					if(ring_frequency == Gear_Position)
					{
						ring_frequency = 0;
						gear_position_last = Gear_Position;
					}
					
				}
			break;
				
			default:
			
		  break;
		}
	}
}

/**************************************************
 * @brie   :Usart_Task()
 * @note   :�������� 
 * @param  :��
 * @retval :��
 **************************************************/
void Usart_Task(void)
{
	static uint8_t usart_step = 0;
	uint8_t result;
	
	if(Power_Flag != 2)
	{
		data.inpVoltage = 0;
		data.rpm = 0;
		data.avgInputCurrent = 0;
		data.dutyCycleNow = 0;
		usart_step = 0;
		return;
	}
	
	switch(usart_step)
	{
		case 0:
			Get_Vesc_Pack_Data(COMM_GET_VALUES);
			usart_step = 1;
		break;
		
		case 1:
			if(VESC_RX_Flag == 1)
			{
				VESC_RX_Flag = 0;
				result = Protocol_Parse(VESC_RX_Buff);
				
				if(result == 0) //�����ɹ�
				{
						//LED1_Filp_Time(500);				
						Usart_Flag = 1;
//						Battery_Voltage = data.inpVoltage; //��ص�ѹ
//						VESC_Rpm = data.rpm;            //ת��
//						AvgInputCurrent = data.avgInputCurrent;  //ĸ�ߵ���
//						DutyCycleNow = data.dutyCycleNow;   //ռ�ձ�
				}
				else	//����ʧ��
				{
						//LED1_Filp_Time(100);
						Usart_Flag = 2;
				}
				Usart_Time = 0;
				usart_step = 2;
			}
			else
			{
				usart_step = 3;
				Usart_Time = 0;
			}
		break;
			
		case 2:
			if(Usart_Time >= 100)
			{
				usart_step = 0;
			}				
		break;
			
		case 3:
			if(VESC_RX_Flag == 1)
			{
				usart_step = 1;
			}
			else if(Usart_Time >= 100)
			{
				usart_step = 0;
			}
		break;
			
		default:
			
		break;
		
	}
	
}
//float k = 0.15;
/**************************************************
 * @brie   :ADC_Task()
 * @note   :ADC���� 
 * @param  :��
 * @retval :��
 **************************************************/
void ADC_Task(void)
{
	static uint8_t adc_step = 0;
//	static uint8_t i = 0;
//	static uint16_t adc_charge_sum[10];
	static uint16_t adc_charge_sum_ave = 0;
	static uint16_t adc1_val_sum_ave = 0;
	static uint16_t adc2_val_sum_ave = 0;
//	float old_charge_current = 0;
	
//	if(Power_Flag != 2)
//	{
//		Charge_Voltage = 0;
//		ADC1_Val = 0;
//		ADC2_Val = 0;
//		adc_step = 0;
//		return;
//	}
	
	switch(adc_step)
	{
		case 0:
			ADC_Time = 0;
			adc_step = 1;
		break;
		
		case 1:
			if(ADC_Time>100)
			{	
				ADC_Time = 0;
				
				adc_charge_sum_ave= Read_ADC_Value(3);
				adc1_val_sum_ave  = Read_ADC_Value(1);
				adc2_val_sum_ave  = Read_ADC_Value(2);
				
				ADC1_Val = (float)(adc1_val_sum_ave*0.0012890625F);
				ADC2_Val = (float)(adc2_val_sum_ave*0.0012890625F);
				
//				if(Charge_Flag == 3)
//				{
//					if(V_I == 1)
//					{
//						V_I = 0;
//						Charge_Time = 0;
//						Sampling_Completion = 0;
//						LED1_OFF; //�ɼ������
//						Charge_Voltage = (float)(adc_charge_sum_ave*0.0257080078125);
//					
//					}
//					else
//					{
//						if(Charge_Time>100)
//						{
//							adc_charge_sum[i] = adc_charge_sum_ave;
//							i++;
//							
//							if(i == 10)
//							{
//								LED1_ON; //�ɼ����ѹ
//								Charge_Time = 0;
//								Sampling_Completion = 1;
//								V_I = 1;
//								i = 0;
//							}
//						}
//					}
//				}
//				else
//				{
//					Charge_Voltage = (float)(adc_charge_sum_ave*0.0257080078125);
//				}
				
				if(V_I == 0)
				{
					if(Charge_Time>100)
					{
						Charge_Current = (float)(-0.008056640625F*adc_charge_sum_ave+16.5F);
						//Charge_Current = Charge_Current*k + old_charge_current*(1-k);
						//old_charge_current = Charge_Current;
					}
				}
				else
				{
					if(Charge_Time>100)
					{
						Charge_Voltage = (float)(adc_charge_sum_ave*0.0257080078125F);
					}
				}
			}
			
//			if(i == 8)
//			{
//				adc_charge_sum_ave >>= 3;
//				// y=kx+b 0=k*2048+b  10=k*(0.65/3.3*4096)+b
//				if(V_I == 0)
//				{
//					Charge_Current = (float)(-0.00806*adc_charge_sum_ave+16.5);
//				}
//				else
//				{
//					Charge_Voltage = (float)(adc_charge_sum_ave*0.0257080078125);
//				}
//				
//				adc_charge_sum_ave = 0;
//				i=0;
//			}
			
		break;
			
	  default:
			
		break;
	}
}

/**************************************************
 * @brie   :Conditional_Judgment()
 * @note   :�����ж�
 * @param  :��
 * @retval :��
 **************************************************/
void Conditional_Judgment(void)
{
	float battery_voltage = 0;
	static float battery_voltage_last = 0;
			
	switch(Power_Flag)
	{
		case 1: //����
			 if(Charge_Voltage > CHARGING_VOLTAGE)
			 {
				Power_Flag = 3;
				Charge_Flag = 1;
			 }
		break;
		
		case 2: //�������
			if(Usart_Flag == 1)
			{
				Usart_Flag = 2;
				
				//DutyCycleNow = 0.9;//������Ҫע��
				if(data.dutyCycleNow < 0)
				{
					data.dutyCycleNow = -data.dutyCycleNow;
				}
				/*duty cycle > DUTY_CYCLE ���������١����١�����*/
				if(data.dutyCycleNow >= DUTY_CYCLE)
				{
					Buzzer_Frequency = ((((uint8_t)(data.dutyCycleNow*100))*4)-220);
				}
				else
				{
					Buzzer_Frequency = 0;
				}
				
				//VESC_Rpm = -10;//������Ҫע��
				
				if(ADC1_Val>2.9F || ADC2_Val > 2.9F)
				{
					if(data.rpm > VESC_RPM_WIDTH)
					{
						Flashlight_Flag = 2;
					}
					else
					{
						Flashlight_Flag = 3;
					}
				}
				else
				{
					Flashlight_Flag = 4;
				}
				
				if(data.rpm<0)
				{
					data.rpm = -data.rpm;
				}
				
				//Battery_Voltage = 82;//������Ҫע��
				
				battery_voltage = (data.inpVoltage+1)/BATTERY_STRING;//+1Ϊ����ֵ
				
				if((battery_voltage > (battery_voltage_last+VOLTAGE_RECEIPT)) || (battery_voltage < (battery_voltage_last - VOLTAGE_RECEIPT)))
				{
					if(battery_voltage>4.07F)
					{
						Power_Display_Flag = 1;
					}
					else if(battery_voltage>4.025F)
					{
						Power_Display_Flag = 2;
					}
					else if(battery_voltage>3.91F)
					{
						Power_Display_Flag = 3;
					}
					else if(battery_voltage>3.834F)
					{
						Power_Display_Flag = 4;
					}
					else if(battery_voltage>3.746F)
					{
						Power_Display_Flag = 5;
					}
					else if(battery_voltage>3.607F)
					{
						Power_Display_Flag = 6;
					}
					else if(battery_voltage>3.49F)
					{
						Power_Display_Flag = 7;
					}
					else if(battery_voltage>3.351F)
					{
						Power_Display_Flag = 8;
					}
					else if(battery_voltage>3.168F)
					{
						Power_Display_Flag = 9;
					}
					else if(battery_voltage>2.81F)
					{
						Power_Display_Flag = 10;
					}
					
					battery_voltage_last = battery_voltage;
				}
				
				
				if(data.avgInputCurrent < 0)
				{
					data.avgInputCurrent = -data.avgInputCurrent;
				}
				//AvgInputCurrent = 1.0;//������Ҫע��
				
				if(data.rpm<VESC_RPM)
				{
					if(ADC1_Val < 2.9F && ADC2_Val <2.9F)
					{
						WS2812_Display_Flag = 1;  //��ʾ����
					}
					else if(ADC1_Val > 2.9F && ADC2_Val > 2.9F)
					{
						WS2812_Display_Flag = 2;  //����ʾ����
						WS2812_Flag = 3;  //10���ƶ�������
					}
					else if(ADC1_Val >2.9F)
					{
						WS2812_Display_Flag = 2;//����ʾ����
						WS2812_Flag = 1;  //���5������     �Ҳ�5���Ʋ�����
					}
					else
					{
						WS2812_Display_Flag = 2;//����ʾ����
						WS2812_Flag = 2;  //���5���Ʋ����� �Ҳ�5������
					}
				}
				else
				{
					if(data.avgInputCurrent < 0.8F && data.rpm < 6000)
					{
						WS2812_Display_Flag = 1; //��ʾ����
					}
					else
					{
						WS2812_Display_Flag = 2; //����ʾ����
						WS2812_Flag = 4; //��10����
					}
				}
				
				if((Charge_Voltage > CHARGING_VOLTAGE) && (data.avgInputCurrent<0.8F))
				{
					if(Charger_Detection_1ms > CHARGER_DETECTION_DELAY)
					{
						Power_Flag = 3;
						Charge_Flag = 1;
						Flashlight_Flag = 0;
						WS2812_Display_Flag =0;
					}
					
				}
				else
				{
					Charger_Detection_1ms = 0;
				}
				/*
					��̤����»�ת�ٴ���1000��ʱ����
					�����Ƚ�̤��ת�ٵ���1000��ʼ��ʱ�������ػ�ʱ��ػ�
				*/
				if(ADC1_Val > 2.9F || ADC2_Val > 2.9F || data.rpm > 1000)
				{
					Shutdown_Time_S = 0;
					Shutdown_Time_M = 0;
				}
				
				if(Shutdown_Time_S>60000)
				{
					Shutdown_Time_S = 0;
					
					Shutdown_Time_M++;
					if(Shutdown_Time_M >= SHUTDOWN_TIME)
					{
						Power_Flag = 3;
					}
				}
			}
		break;
		
		case 3: //VESC�ػ�������������ӹ���
			if(V_I == 0 && Charge_Time > 150)
			{
				if(Charge_Current < CHARGE_CURRENT && Charge_Current > 0)
				//if(Charge_Current > CHARGE_CURRENT_L && Charge_Current < CHARGE_CURRENT_H)
				{
					Shutdown_Cnt++;
					if(Shutdown_Cnt>10)
					{
//						Charge_Flag = 3;
						Shutdown_Cnt = 0;
						CHARGE_OFF;  //�رճ����
					}
				}
				else
				{
					Shutdown_Cnt = 0;
				}
			}
			else if(Charge_Time > 150)
			{
				battery_voltage = (Charge_Voltage+1)/BATTERY_STRING;//+1Ϊ����ֵ
				if(Charge_Flag == 2)
				{
					if((battery_voltage > (battery_voltage_last+VOLTAGE_RECEIPT)) || (battery_voltage < (battery_voltage_last - VOLTAGE_RECEIPT)))
					{
						if(battery_voltage>4.07F)
						{
							Power_Display_Flag = 1;
						}
						else if(battery_voltage>4.025F)
						{
							Power_Display_Flag = 2;
						}
						else if(battery_voltage>3.91F)
						{
							Power_Display_Flag = 3;
						}
						else if(battery_voltage>3.834F)
						{
							Power_Display_Flag = 4;
						}
						else if(battery_voltage>3.746F)
						{
							Power_Display_Flag = 5;
						}
						else if(battery_voltage>3.607F)
						{
							Power_Display_Flag = 6;
						}
						else if(battery_voltage>3.49F)
						{
							Power_Display_Flag = 7;
						}
						else if(battery_voltage>3.351F)
						{
							Power_Display_Flag = 8;
						}
						else if(battery_voltage>3.168F)
						{
							Power_Display_Flag = 9;
						}
						else if(battery_voltage>2.81F)
						{
							Power_Display_Flag = 10;
						}
						battery_voltage_last = battery_voltage;
					}
				}
			}
				
				
			
				
				
		break;
		
		default:
			if(Charge_Voltage > CHARGING_VOLTAGE)
			 {
				Power_Flag = 3;
				Charge_Flag = 1;
			 }
		break;
			
	}
}














