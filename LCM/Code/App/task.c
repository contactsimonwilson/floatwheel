#include "task.h"
#include "eeprom.h"
#include <math.h>


///Colors
//These are warnings displayed on the lightbar -> use full brightness
uint8_t purple[3] = {0x80, 0x00, 0x80};		//Tiltback - high, low, duty
uint8_t red[3] = {0xff, 0x00, 0x00};		//Error
uint8_t orange[3] = {0xff, 0x5a, 0x00};		//Temp
uint8_t yellow[3] = {0xff, 0xff, 0x00};		//Current

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
 * @note   Cycles through the available lighting profiles
 * @param  persist (bool): whether to save the current profile to EEPROM
 **************************************************/
void Change_Light_Profile(bool persist) {
	// Change light profile
	Light_Profile++; 
	if(Light_Profile == 4)
	{
		Light_Profile = 1;
	}
	if (persist) {
		EEPROM_WriteByte(0, Light_Profile);
	}
}

void Change_Cell_Type(uint8_t type) {
	if (type == DG40 || type == P42A) {
		EEPROM_WriteByte(CHANGE_CELL_TYPE, type);
	}
}

void Change_Boot_Animation(uint8_t animation) {
	if (animation == RAINBOW || animation == NORMAL) {
		EEPROM_WriteByte(CHANGE_BOOT_ANIMATION, animation);
	} 
}

/*
void Change_Cell_Type(uint8_t type, bool get) {
	if ((type == DG40 || type == P42A) & get) {
		EEPROM_WriteByte(CHANGE_CELL_TYPE, type);
	} else {
		EEPROM_ReadByte(CHANGE_CELL_TYPE, type);
	}
}

void Change_Boot_Animation(uint8_t animation,bool get) {
	if ((animation == RAINBOW || animation == NORMAL) & get) {
		EEPROM_WriteByte(CHANGE_BOOT_ANIMATION, animation);
	} else {
		EEPROM_ReadByte(CHANGE_BOOT_ANIMATION, animation);
	}
}*/

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
				Change_Light_Profile(true);			
			}
		break;
		
		case 3:		//����
			Power_Flag = 3;  //VESC�ػ�
			Flashlight_Flag = 0;
			Lightbar_Mode_Flag =0;
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
 * @note	Displays current power level on lightbar
 **************************************************/
void Power_Display(void)
{
	uint8_t i;
	uint8_t num = 10 - (Power_Display_Flag - 1);

	for (i=0;i<10;i++) {
		if (Power_Display_Flag == 10) {
			// Something is wrong
			WS2812_Set_Colour(i,WS2812_Measure,0,0);
		} else {
			if (i < num) {
				if (num <= 2) {
					WS2812_Set_Colour(i,WS2812_Measure,0,0);
				} else {
					WS2812_Set_Colour(i,WS2812_Measure,WS2812_Measure,WS2812_Measure);
				}
			} else {
				WS2812_Set_Colour(i,0,0,0);
			}
		}
	}
	
	WS2812_Refresh();//ˢ����ʾ
}

/**************************************************
 * @note	Displays current footpad sensor activation on the lightbar
 **************************************************/
void Sensor_Activation_Diplay(void)
{
	uint8_t i;
	
	switch(Footpad_Activation_Flag)
	{
		case 1:// adc1>2.ADC_THRESHOLD_LOWER  adc2<2.ADC_THRESHOLD_LOWER
			for(i=0;i<5;i++)
			{
				WS2812_Set_Colour(i,0,0,WS2812_Measure);
			}
				for(i=5;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
		
		case 2:// adc1<2.ADC_THRESHOLD_LOWER  adc2>2.ADC_THRESHOLD_LOWER
			for(i=0;i<5;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
				for(i=5;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,WS2812_Measure);
			}
		break;
		
		case 3:// adc1>2.ADC_THRESHOLD_LOWER  adc2>2.ADC_THRESHOLD_LOWER
			for(i=0;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,WS2812_Measure);
			}
		break;
			
		case 4:// adc1<ADC_THRESHOLD_LOWER.5V  adc2<2.ADC_THRESHOLD_LOWER
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
 * @note	Displays the boot animation on the lightbar
 **************************************************/
void WS2812_Boot(void) {
	uint8_t i;
	uint8_t num = floor(Power_Time / 500) + 1;
	uint8_t rgbMap[10][3] = {{255,0,0}, {255,127,0}, {255,255,0}, {127,255,0}, {0,255,0}, {0,255,127}, {0,255,255}, {0,127,255}, {0,0,255}, {127,0,255}};

	if (num > 10) {
		num = 10;
	}

	for (i=0;i<num;i++) {
		switch (BOOT_ANIMATION) {
			case NORMAL:
				WS2812_Set_Colour(i,0,255,255);
			break;
			case RAINBOW:
				WS2812_Set_Colour(i,rgbMap[i][0],rgbMap[i][1],rgbMap[i][2]);
			break;
		}
	}

	for (i = num; i < 10; i++) {
		WS2812_Set_Colour(i,0,0,0);
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
 * @note	Shows the current battery % when the board is charging
 **************************************************/
void WS2812_Charge(void)
{
	uint8_t i;
	uint8_t num = 10 - (Power_Display_Flag - 1);
	static uint8_t cnt = 0;
	uint8_t brightness = 0;
	
	brightness = WS2812_Cal_Bri(cnt);
	for (i=0;i<10; i++) {
		if (i <= num) {
			if (num >= 10) {
				// Full charged
				WS2812_Set_Colour(i,0,brightness,0);
			} else if (num <= 2) {
				// Low battery
				WS2812_Set_Colour(i,brightness,0,0);
			} else {
				// Normal charging
				WS2812_Set_Colour(i,brightness,brightness,brightness);
			}
		} else {
			WS2812_Set_Colour(i,0,0,0);
		}
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
//	static uint8_t Footpad_Activation_Flag_last = 0; //��һ�ε�״̬
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
			
			Lightbar_Mode_Flag = 0;
			Footpad_Activation_Flag = 0;
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
	
	switch(Light_Profile)
	{
		// Inversely set the brightness of the lightbar to the brightness of the main lights
		case 1: //1��
			WS2812_Measure = LIGHTBAR_BRIGHTNESS_1;
		break;
		
		case 2:	//2��
			WS2812_Measure = LIGHTBAR_BRIGHTNESS_2;
		break;
		
		case 3: //3��
			WS2812_Measure = LIGHTBAR_BRIGHTNESS_3;
		break;
		
		default:
			
		break;
	}
	
	if(Lightbar_Mode_Flag == 1)  //��ʾ����
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
//		if(Footpad_Activation_Flag_last == Footpad_Activation_Flag) //��һ�κ���һ��һ��ֱ���˳�
//		{
//			return;
//		}
//		else
//		{
//			Footpad_Activation_Flag_last = Footpad_Activation_Flag;
//			WS2812();//����ʾ����WS2812
//		}
		Sensor_Activation_Diplay();//����ʾ����WS2812
	}
	
}

/**************************************************
 * @note	Sets appropriate flags for current power state
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
					if (Power_Time > VESC_BOOT_TIME)
					{
						Power_Flag = 2; //�������
						Light_Profile = 1; //������Ĭ����1��
						Buzzer_Flag = 2;    //����Ĭ�Ϸ�������
						power_step = 0;

						// Read saved value from EEPROM
						uint8_t data = Light_Profile;
						EEPROM_ReadByte(0, &data);

						if (data > 0 && data < 4) {
							Light_Profile = data;
						}

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
 * @note	Sets appropriate flags for current charging state
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
				switch(Light_Profile)
				{
					case 1:
						brightness = (Flashlight_Time*1)+1000;
						brightness = 9999-brightness+1;
					break;
					
					case 2:
						brightness = ((Flashlight_Time*2.5)+1000);
						brightness = 9999-brightness+1;
					break;
					
					case 3:
						brightness = (Flashlight_Time*4.5)+1000;
						brightness = 9999-brightness+1;
					break;
					
					default:
						
					break;
				}
				
				TIM_SetCompare2(TIM1,brightness);
			}
			if(Flashlight_Time >= 2000)
			{
				switch(Light_Profile)
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
 * @note	Controls headlight/taillight brightness multiplier and direction
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
	static uint8_t Light_Profile_last = 0;
		
	if(Light_Profile_last == Light_Profile && Flashlight_Detection_Time >= 3100)
	{
		Flashlight_Detection_Time = 3100;
		return;
	}
	else
	{
		if(Light_Profile_last != Light_Profile)
		{
			if(ADC1_Val < ADC_THRESHOLD_LOWER && ADC2_Val < ADC_THRESHOLD_LOWER)
			{
				switch(Light_Profile)
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
				switch(Light_Profile)
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
			Light_Profile_last = Light_Profile;
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
	static uint8_t Light_Profile_last = 0; //��һ�εĵ�λ
	static uint8_t ring_frequency = 0;
	static uint16_t sound_frequency = 0;
	
	if(Power_Flag != 2 || Buzzer_Flag == 1) //VESC�ϵ��������ر� 
	{
		BUZZER_OFF;
		buzzer_step = 0;
		return;
	}
	
	if(Buzzer_Frequency == 0 && Light_Profile_last == Light_Profile) //���������Ƶ��Ϊ0����һ�εĵ�λ������εĵ�λ
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
				sound_frequency = (uint16_t)(-2.78*Buzzer_Frequency+666);
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
					if(ring_frequency == Light_Profile)
					{
						ring_frequency = 0;
						Light_Profile_last = Light_Profile;
					}
					
				}
			break;
				
			default:
			
		  break;
		}
	}
}

/**************************************************
 * @note	Sends commands to VESC controller to get data
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
/**************************************************
 * @note	Sets appropriate flags for current ADC/footpad sensor state
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
				
				ADC1_Val = (float)(adc1_val_sum_ave*0.0012890625);
				ADC2_Val = (float)(adc2_val_sum_ave*0.0012890625);
				
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
						Charge_Current = (float)(-0.008056640625*adc_charge_sum_ave+16.5);
						//Charge_Current = Charge_Current*k + old_charge_current*(1-k);
						//old_charge_current = Charge_Current;
					}
				}
				else
				{
					if(Charge_Time>100)
					{
						Charge_Voltage = (float)(adc_charge_sum_ave*0.0257080078125);
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
 * @note Apply the corresponding battery level based on current voltage
 **************************************************/
void Apply_BatteryPowerFlag(float battery_voltage) {
	float battVoltages[10] =  {4.054, 4.01, 3.908, 3.827, 3.74, 3.651, 3.571, 3.485, 3.38, 3.0}; // P42A

	if (CELL_TYPE == DG40) {
		// DG40
		float dg40BattVoltages[10] = {4.07, 4.025, 3.91, 3.834, 3.746, 3.607, 3.49, 3.351, 3.168, 2.81};

		for (int i=0;i<10;i++) {
			battVoltages[i] = dg40BattVoltages[i];
		}
	}
	
	for (int i=0;i<10;i++) {
		if (battery_voltage > battVoltages[i]) {
			Power_Display_Flag = i + 1;
			break;
		}
		// Between zero and min voltage
		if (i == 9) {
			Power_Display_Flag = 10;
		}
	}
}

/**************************************************
 * @note The main task for deyermiming how to display the lights
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
				
				if(ADC1_Val>ADC_THRESHOLD_UPPER || ADC2_Val > ADC_THRESHOLD_UPPER)
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
				
				if((battery_voltage > (battery_voltage_last+VOLTAGE_RECEIPT)) || (battery_voltage < (battery_voltage_last - VOLTAGE_RECEIPT))) {
					Apply_BatteryPowerFlag(battery_voltage);
					battery_voltage_last = battery_voltage;
				}
				
				
				if(data.avgInputCurrent < 0)
				{
					data.avgInputCurrent = -data.avgInputCurrent;
				}
				//AvgInputCurrent = 1.0;//������Ҫע��
				
				if(data.rpm<VESC_RPM)
				{
					if(ADC1_Val < ADC_THRESHOLD_UPPER && ADC2_Val < ADC_THRESHOLD_UPPER)
					{
						Lightbar_Mode_Flag = 1;  //��ʾ����
					}
					else if(ADC1_Val > ADC_THRESHOLD_UPPER && ADC2_Val > ADC_THRESHOLD_UPPER)
					{
						Lightbar_Mode_Flag = 2;  //����ʾ����
						Footpad_Activation_Flag = 3;  //10���ƶ�������
					}
					else if(ADC1_Val >ADC_THRESHOLD_UPPER)
					{
						Lightbar_Mode_Flag = 2;//����ʾ����
						Footpad_Activation_Flag = 1;  //���5������     �Ҳ�5���Ʋ�����
					}
					else
					{
						Lightbar_Mode_Flag = 2;//����ʾ����
						Footpad_Activation_Flag = 2;  //���5���Ʋ����� �Ҳ�5������
					}
				}
				else
				{
					if(data.avgInputCurrent < 0.8 && data.rpm < 6000)
					{
						Lightbar_Mode_Flag = 1; //��ʾ����
					}
					else
					{
						Lightbar_Mode_Flag = 2; //����ʾ����
						Footpad_Activation_Flag = 4; //��10����
					}
				}
				
				if((Charge_Voltage > CHARGING_VOLTAGE) && (data.avgInputCurrent<0.8))
				{
					if(Charger_Detection_1ms > CHARGER_DETECTION_DELAY)
					{
						Power_Flag = 3;
						Charge_Flag = 1;
						Flashlight_Flag = 0;
						Lightbar_Mode_Flag =0;
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
				if(ADC1_Val > ADC_THRESHOLD_UPPER || ADC2_Val > ADC_THRESHOLD_UPPER || data.rpm > 1000)
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
					if((battery_voltage > (battery_voltage_last+VOLTAGE_RECEIPT)) || (battery_voltage < (battery_voltage_last - VOLTAGE_RECEIPT))) {
						Apply_BatteryPowerFlag(battery_voltage);
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
