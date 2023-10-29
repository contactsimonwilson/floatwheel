#include "task.h"
#include "math.h"

/**************************************************
 * @brie   :LED_Task()
 * @note   :LED任务 
 * @param  :无
 * @retval :无
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
 * @note   :KEY1任务
 * @param  :无
 * @retval :无
 **************************************************/
void KEY1_Task(void)
{
	if(KEY1_State == 0 || Power_Flag == 3)  //充电器供电按键不起作用
	{
		return;
	}
	
	switch(KEY1_State)
	{
		case 1:  	//单击
			if(Power_Flag != 2)
			{
				Power_Flag = 1;  //VESC开机
			}	
		break;
		
		case 2:		//双击	
			if(Power_Flag == 2) //开机完成
			{
				Gear_Position++;
				if(Gear_Position == 4)
				{
					Gear_Position = 1;
				}
			}
		break;
		
		case 3:		//长按
			Power_Flag = 3;  //VESC关机
			Flashlight_Flag = 0;
			WS2812_Display_Flag =0;
		break;
		
		case 4:		//三按
			if(Power_Flag == 2) //开机完成
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
 * @note   :display 1..10 leds depending on power level
 **************************************************/
void Power_Display(uint8_t brightness)
{
	uint8_t numleds = 11 - Power_Display_Flag;
	uint8_t r, g, b = 0;
	// 20% and below: red
	// 40% and below: yellow
	// > 40% white
	r = brightness;
	if (numleds > 2)
		g = WS2812_Measure;
	if (numleds > 4)
		b = WS2812_Measure;
	WS2812_Set_AllColours(0, numleds, r, g, b);
	WS2812_Refresh();
}

/**************************************************
 * @brie   :WS2812()
 * @note   :不显示电量WS2812
 * @param  :无
 * @retval :无
 **************************************************/
void WS2812(void)
{
	uint8_t i;
	uint8_t pos, red;
	uint8_t green = 0;
	uint8_t blue = WS2812_Measure;
	if (data.floatPackageSupported) {
		// make footpad indicators purple if float package commands are received successfully!
		green = WS2812_Measure / 3;
		blue = WS2812_Measure / 3;
	}
	
	switch(WS2812_Flag)
	{
		case 1:// Half Foot Sensors: adc1>2.5V  adc2<2.5V
				WS2812_Set_AllColours(1, 5,0,green, blue);
		break;
		
		case 2:// Half Foot Sensors: adc1<2.5V  adc2>2.5V
				WS2812_Set_AllColours(6, 10,0,green, blue);
		break;
		
		case 3:// Both Foot Sensors: adc1>2.5V  adc2>2.5V
				WS2812_Set_AllColours(1, 10,0,green,blue);
		break;
			
		case 4:// Riding
			
		  if ((data.state != RUNNING_WHEELSLIP) && (lcmConfig.statusbarMode == 0)) {
				if (data.dutyCycleNow > 90) {
					WS2812_Set_AllColours(1, 10,WS2812_Measure,0,0);
				}
				else if (data.dutyCycleNow > 85) {
					WS2812_Set_AllColours(1, 9,WS2812_Measure,0,0);
				}
				else if (data.dutyCycleNow > 80) {
					WS2812_Set_AllColours(1, 8,WS2812_Measure,WS2812_Measure/2,0);
				}
				else if (data.dutyCycleNow > 70) {
					WS2812_Set_AllColours(1, 7,WS2812_Measure/3,WS2812_Measure/3,0);
				}
				else if (data.dutyCycleNow > 60) {
					WS2812_Set_AllColours(1, 6,0,WS2812_Measure/3,0);
				}
				else if (data.dutyCycleNow > 50) {
					WS2812_Set_AllColours(1, 5,0,WS2812_Measure/4,0);
				}
				else {
					WS2812_Set_AllColours(1, 10,0,0,0);
				}
			}
		break;

		case 5:
			// Flywheel Mode: just a rando pattern fpr now
			red = Power_Time % 255;
			green = (Power_Time + 100) % 255;
		  blue = (Power_Time - 100) % 255;
		  pos = (Power_Time/100) % 10;
			WS2812_Set_Colour(pos,green,red,blue);
		break;			
		default:
			for(i=0;i<10;i++)
			{
				WS2812_Set_Colour(i,0,0,0);
			}
		break;
	}
	WS2812_Refresh();//刷新显示
}


/**************************************************
 * @brie   :WS2812_Boot()
 * @note   :Boot Animation
 **************************************************/
void WS2812_Boot(void)
{
	uint8_t i;
	uint8_t num = floor(Power_Time / 100) + 1;
	uint8_t rgbMap[10][3] = {{255,0,0}, {255,127,0}, {255,255,0}, {127,255,0}, {0,255,0}, {0,255,127}, {0,255,255}, {0,127,255}, {0,0,255}, {127,0,255}};

	while (num > 10) {
		num -= 10;
	}
	for (i=0;i<num;i++) {
		WS2812_Set_Colour(i,rgbMap[i][0],rgbMap[i][1],rgbMap[i][2]);
	}

	for (i = num; i < 10; i++) {
		if (i == num)
			WS2812_Set_Colour(i,rgbMap[i][0]/3,rgbMap[i][1]/3,rgbMap[i][2]/3);
		else
			WS2812_Set_Colour(i,0,0,0);
	}

	WS2812_Refresh();
}




uint8_t brightness = 1;
/**************************************************
 * @brie   :WS2812_Cal_Bri()
 * @note   :计算亮度
 * @param  :次数 1次表示200ms
 * @retval :亮度
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
 * @note   :Power LED display while charging
 **************************************************/
void WS2812_Charge(void)
{
	uint8_t i;
	uint8_t num;
	static uint8_t cnt = 0;
	uint8_t brightness = 0;	
	brightness = WS2812_Cal_Bri(cnt);
	Power_Display(brightness);
	
	cnt++;
	if(cnt == 100)
	{
		cnt = 0;
	}
	
	WS2812_Refresh();
}	

/**************************************************
 * @brie   :WS2812_Task()
 * @note   :WS2812任务 
 * @param  :无
 * @retval :无
 **************************************************/
void WS2812_Task(void)
{
//	static uint8_t ws2812_flag_last = 0; //上一次的状态
//	static uint8_t power_display_flag_last = 0; //上一次的状态
	uint8_t i;

	if(WS2812_Counter < 20) //20ms刷新一次
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
			WS2812_Refresh();//刷新显示
			
			WS2812_Display_Flag = 0;
			WS2812_Flag = 0;
			Power_Display_Flag = 0;
			
			return;
	}
	
	if(Power_Flag == 1)
	{
		WS2812_Boot();  //开机启动
		return;
	}
	
	if(Charge_Flag == 3) //电池电充满了
	{
		for(i=0;i<10;i++)
		{
			WS2812_Set_Colour(i,255,255,255);
		}
		return;
	}
	
	if(Charge_Flag == 2) //充电呼吸显示
	{
		WS2812_Charge();
		return;
	}
	
	if (lcmConfig.isSet) {
		WS2812_Measure = lcmConfig.statusbarBrightness;
	}
	else switch(Gear_Position)
	{
		case 1: //1挡
			WS2812_Measure = WS2812_1_BRIGHTNESS;
		break;
		
		case 2:	//2挡
			WS2812_Measure = WS2812_2_BRIGHTNESS;
		break;
		
		case 3: //3挡
			WS2812_Measure = WS2812_3_BRIGHTNESS;
		break;
		
		default:
			
		break;
	}
	
	if(WS2812_Display_Flag == 1)  // I think this is when the board is idle
	{
		if (data.state == DISABLED) {
			int brightness = WS2812_Measure;
			if (brightness < 20)
				brightness = 30;
			WS2812_Set_AllColours(5, 6, brightness, 0, 0);
		}
		else {
			Power_Display(WS2812_Measure);	// Display power level
		}
	}
	else //不显示电量
	{
//		if(ws2812_flag_last == WS2812_Flag) //这一次和上一次一样直接退出
//		{
//			return;
//		}
//		else
//		{
//			ws2812_flag_last = WS2812_Flag;
//			WS2812();//不显示电量WS2812
//		}
		WS2812();//不显示电量WS2812
	}
	
}

/**************************************************
 * @brie   :Power_Task()
 * @note   :电源任务 
 * @param  :无
 * @retval :无
 **************************************************/
void Power_Task(void)
{
	static uint8_t power_flag_last = 0; //上一次的状态
	static uint8_t power_step = 0;
	
	if(power_flag_last == Power_Flag && Power_Flag != 1)
	{
		return;
	}
	power_flag_last = Power_Flag;
	
	switch(Power_Flag)
	{
		case 1://VESC开机
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
						Power_Flag = 2; //开机完成
						Gear_Position = 1; //开机后默认是1挡
						Buzzer_Flag = 2;    //开机默认蜂鸣器响
						power_step = 0;
					}
				break;
			}
			
		break;	
		
		case 3://VESC关机，充电器给板子供电
			PWR_OFF;
			//LED1_Filp_Time(1000);	
			//Charge_Flag = 1; //准备充电
		break;
		
		default:
			
		break;
	}
}

/**************************************************
 * @brie   :Charge_Task()
 * @note   :充电任务 
 * @param  :无
 * @retval :无
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
			if(Charge_Time > 1000)  //延时1S
			{
				charge_step = 2;
			}
		break;
		
		case 2:
			CHARGE_ON;  //打开充电器
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
				LED1_ON; //采集充电电压
				charge_step = 5;
			}
		break;
			
		case 5:
			if(Charge_Time > DETECTION_SWITCH_TIME) 
			{
				V_I = 0;
				Charge_Time = 0;
				LED1_OFF; //采集充电流
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
 * @note   :照明灯亮度
 * @param  :red_white = 1 前照明灯白 后照明灯红
 *          red_white = 2 前照明灯红 后照明灯白
 *          bright = 1    亮度从0% -10% 2秒
 *          bright = 2    亮度从10%-100% 2秒
 * @retval :无
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
		TIM_SetCompare2(TIM1,9500);//从10%开始
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
				TIM_SetCompare2(TIM1,9999); //从0%开始
				flashlight_bright_step = 3;
			}
			else
			{
				TIM_SetCompare2(TIM1,9500);//从10%开始
				flashlight_bright_step = 4;
			}
		break;
		
		case 3://亮度从0% -10% 2秒
			if(Flashlight_Time%2 == 0)
			{
				brightness = Flashlight_Time/2;
				brightness = 9999-brightness+1;
				TIM_SetCompare2(TIM1,brightness);
			}
			if(Flashlight_Time >= 2000)
			{
				TIM_SetCompare2(TIM1,9500);
				flashlight_bright_step = 5;
			}
		break;
		
		case 4://亮度从10%-100% 2秒
		
			if(Flashlight_Time%2 == 0)
			{
				switch(Gear_Position)
				{
					case 1:
						brightness = (Flashlight_Time*1)+1000;
						brightness = 9999;
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
				if (lcmConfig.isSet) {
					TIM_SetCompare2(TIM1,9999 - lcmConfig.headlightBrightness*39);
				}
				else {
					switch(Gear_Position)
					{
						case 1:
							TIM_SetCompare2(TIM1,9999);
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
				}
				
				flashlight_bright_step = 5;
			}
		break;
		
		case 5://亮度调整完
			Brightness_Flag = 2;
			flashlight_bright_step = 0;
		break;
		
		default:
			
		break;
	}

}
	
/**************************************************
 * @brie   :Flashlight_Task()
 * @note   :照明灯任务 
 * @param  :无
 * @retval :无
 **************************************************/
void Flashlight_Task(void)
{
	static uint8_t flashlight_flag_last = 0;
	
	if(Power_Flag == 3 || Power_Flag == 0) //VESC断电照明灯关闭
	{
		LED_B_OFF;
		LED_F_OFF;
		TIM_SetCompare2(TIM1,0);
		return;
	}
	
	if(flashlight_flag_last == Flashlight_Flag && Brightness_Flag == 2) //亮度已经调整好
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
		case 1://VESC刚上电前后照明灯量度从0%经过2秒达到10%
			Flashlight_Bright(1,1);
		break; 
		
		case 2://VESC前面白灯后面红灯(正转)
			Flashlight_Bright(1,2);
		break;
		
		case 3://VESC前面红灯后面白灯(反转)
			Flashlight_Bright(2,2);
		break;
		
		case 4://VESC前面红灯后面白灯(反转)
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
			if(ADC1_Val < 2.5 && ADC2_Val < 2.5)
			{
				if (lcmConfig.isSet) {
					TIM_SetCompare2(TIM1,9999 - lcmConfig.headlightBrightness*39);
				}
				else {
					switch(Gear_Position)
					{
						case 1:
							TIM_SetCompare2(TIM1,9999);
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
				}
				Flashlight_Detection_Time = 0;
			}
			else
			{
				if (lcmConfig.isSet) {
					TIM_SetCompare2(TIM1,9999 - lcmConfig.headlightBrightness*39);
				}
				else {
					switch(Gear_Position)
					{
						case 1:
							TIM_SetCompare2(TIM1,9999);
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
				}
				Flashlight_Detection_Time = 3100;
			}
			gear_position_last = Gear_Position;
		}
		else
		{
			if(Flashlight_Detection_Time >= 3000)
			{
				TIM_SetCompare2(TIM1,9500);
				Flashlight_Detection_Time = 3100;
			}
		}
		
	}
}
/**************************************************
 * @brie   :Buzzer_Task()
 * @note   :蜂鸣器任务 
 * @param  :无
 * @retval :无
 **************************************************/
void Buzzer_Task(void)
{
	static uint8_t buzzer_step = 0;
	static uint8_t gear_position_last = 0; //上一次的档位
	static uint8_t ring_frequency = 0;
	static uint16_t sound_frequency = 0;
	
	if(Power_Flag != 2 || Buzzer_Flag == 1) //VESC断电或蜂鸣器关闭 
	{
		BUZZER_OFF;
		buzzer_step = 0;
		return;
	}
	
	if(Buzzer_Frequency == 0 && gear_position_last == Gear_Position) //蜂鸣器响的频率为0或上一次的档位等于这次的档位
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
 * @note   :串口任务 
 * @param  :无
 * @retval :无
 **************************************************/
void Usart_Task(void)
{
	static uint8_t usart_step = 0;
	
	uint8_t result;

  if(Charge_Flag)
		return;
	
	if(Power_Flag != 2)
	{
		// legacy/motor data
		data.rpm = 0;
		data.dutyCycleNow = 0;
		data.avgInputCurrent = 0;
		data.inpVoltage = 0;

		// float package data
		data.floatPackageSupported = false;
		data.state = 255;
		data.fault = 0;

		lcmConfig.isSet = false;
		lcmConfig.statusbarMode = 0;

		usart_step = 0;
		
		return;
	}
	
	switch(usart_step)
	{
		case 0:
			if ((data.floatPackageSupported == false) && (Power_Time > VESC_BOOT_TIME * 2))
				Get_Vesc_Pack_Data(COMM_GET_VALUES);
			else
				Get_Vesc_Pack_Data(COMM_CUSTOM_APP_DATA);

			usart_step = 1;
		break;
		
		case 1:
			if(VESC_RX_Flag == 1)
			{
				VESC_RX_Flag = 0;
				result = Protocol_Parse(VESC_RX_Buff);
				
				if(result == 0) //解析成功
				{
						//LED1_Filp_Time(500);				
						Usart_Flag = 1;
//						Battery_Voltage = data.inpVoltage; //电池电压
//						VESC_Rpm = data.rpm;            //转速
//						AvgInputCurrent = data.avgInputCurrent;  //母线电流
//						DutyCycleNow = data.dutyCycleNow;   //占空比
				}
				else	//解析失败
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
 * @note   :ADC任务 
 * @param  :无
 * @retval :无
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
//						LED1_OFF; //采集充电流
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
//								LED1_ON; //采集充电压
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

void CheckPowerLevel(float battery_voltage)
{
	static float battery_voltage_last = 0;

	if((battery_voltage > (battery_voltage_last+VOLTAGE_RECEIPT)) || (battery_voltage < (battery_voltage_last - VOLTAGE_RECEIPT)))
	{
		if(battery_voltage>4.07)
		{
			Power_Display_Flag = 1;
		}
		else if(battery_voltage>4.025)
		{
			Power_Display_Flag = 2;
		}
		else if(battery_voltage>3.91)
		{
			Power_Display_Flag = 3;
		}
		else if(battery_voltage>3.834)
		{
			Power_Display_Flag = 4;
		}
		else if(battery_voltage>3.746)
		{
			Power_Display_Flag = 5;
		}
		else if(battery_voltage>3.607)
		{
			Power_Display_Flag = 6;
		}
		else if(battery_voltage>3.49)
		{
			Power_Display_Flag = 7;
		}
		else if(battery_voltage>3.351)
		{
			Power_Display_Flag = 8;
		}
		else if(battery_voltage>3.168)
		{
			Power_Display_Flag = 9;
		}
		else if(battery_voltage>2.81)
		{
			Power_Display_Flag = 10;
		}

		battery_voltage_last = battery_voltage;
	}
}

/**************************************************
 * @brie   :Conditional_Judgment()
 * @note   :条件判断
 * @param  :无
 * @retval :无
 **************************************************/
void Conditional_Judgment(void)
{
	switch(Power_Flag)
	{
		case 1: //开机
			 if(Charge_Voltage > CHARGING_VOLTAGE)
			 {
				//Power_Flag = 3;
				Charge_Flag = 1;
			 }
		break;
		
		case 2: //开机完成
			if(Usart_Flag == 1)
			{
				Usart_Flag = 2;
				
				if(data.dutyCycleNow < 0)
				{
					data.dutyCycleNow = -data.dutyCycleNow;
				}
				// Duty Cycle beep
				if ((lcmConfig.dutyBeep > 0) && (data.dutyCycleNow >= lcmConfig.dutyBeep))
				{
					Buzzer_Frequency = ((((uint8_t)(data.dutyCycleNow))*4)-220);
				}
				else
				{
					Buzzer_Frequency = 0;
				}
				
				// Don't buzz in wheel slip or flywheel mode
				if (data.state > RUNNING_UPSIDEDOWN) {
					Buzzer_Frequency = 0;
				}
				
				if(ADC1_Val>2.9 || ADC2_Val > 2.9)
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
				
				// Riding? Get voltage from VESC
				CheckPowerLevel((data.inpVoltage+1)/BATTERY_STRING);
				
				if(data.avgInputCurrent < 0)
				{
					data.avgInputCurrent = -data.avgInputCurrent;
				}

				if(data.state == RUNNING_FLYWHEEL) {
					WS2812_Display_Flag = 2;
					WS2812_Flag = 5;
					Buzzer_Frequency = 0;
				}
				else if(data.rpm<VESC_RPM)
				{
					if (data.state == DISABLED) {
						if ((ADC1_Val > 2) || (ADC2_Val > 2)) {
							// Don't touch my board when it's disabled :)
							Buzzer_Frequency = ((((uint8_t)(0.5*100))*4)-220);
						}
					}
					else {
						Buzzer_Frequency = 0;

						if(ADC1_Val < 2.9 && ADC2_Val <2.9)
						{
							if(data.avgInputCurrent < 1.0)
							{
								WS2812_Display_Flag = 1;
							}
						}
						else {
							WS2812_Display_Flag = 2;
							if(ADC1_Val > 2.9 && ADC2_Val > 2.9)
							{
								WS2812_Flag = 3;
							}
							else if(ADC1_Val >2.9)
							{
								WS2812_Flag = 1;
							}
							else
							{
								WS2812_Flag = 2;
							}
						}
					}
				}
				else
				{
					// Add check for low voltage to force voltage display on WS2812!
						WS2812_Display_Flag = 2;
						WS2812_Flag = 4;	// Normal Riding!
				}
				
				if((Charge_Voltage > CHARGING_VOLTAGE) && (data.avgInputCurrent<0.8))
				{
					if(Charger_Detection_1ms > CHARGER_DETECTION_DELAY)
					{
						//Power_Flag = 3;
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
					脚踏板踩下或转速大于1000定时清零
					即不踩脚踏板转速低于1000开始计时，超过关机时间关机
				*/
				if(ADC1_Val > 2.9 || ADC2_Val > 2.9 || data.rpm > 1000)
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
		
		case 3: //VESC关机，充电器给板子供电
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
						CHARGE_OFF;  //关闭充电器
					}
				}
				else
				{
					Shutdown_Cnt = 0;
				}
			}
			else if(Charge_Time > 150)
			{
				if(Charge_Flag == 2)
				{
					CheckPowerLevel((Charge_Voltage+1)/BATTERY_STRING);
				}
			}
				
		break;
		
		default:
			if(Charge_Voltage > CHARGING_VOLTAGE)
			 {
				//Power_Flag = 3;
				Charge_Flag = 1;
			 }
			 else {
				 Charge_Flag = 0;
			 }
		break;
			
	}
}














