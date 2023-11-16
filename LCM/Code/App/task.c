#include "task.h"
#include "math.h"

/**************************************************
+ * Reset LCM Config
+ **************************************************/
static void lcmConfigReset(void)
{
	lcmConfig.isSet = false;
	lcmConfig.headlightBrightness = 0;
	lcmConfig.statusbarBrightness = 30;
	lcmConfig.statusbarMode = 0;
	lcmConfig.dutyBeep = 90;
	lcmConfig.boardOff = 0;
	errCode = 0;
}

/**************************************************
 * @brie   :KEY1_Task()
 * @note   :KEY1任务
 * @param  :无
 * @retval :无
 **************************************************/
void KEY1_Task(void)
{
	if(KEY1_State == 0)// || Power_Flag == 3)  //充电器供电按键不起作用
	{
		return;
	}
	
	switch(KEY1_State)
	{
		case 1:         // Click
			if(Power_Flag != 2)
			{
				Power_Flag = 1;  // VESC power on
			}
		break;

		case 2:         // Double click
			if(Power_Flag == 2) // Power on completed
			{
				Gear_Position++;
				if(Gear_Position == 4)
				{
					Gear_Position = 1;
				}
			}
		break;

		case 3:         // Long press
			if (Power_Flag < 3) {
				lcmConfigReset();
				Power_Flag = 4;  // VESC power off
				Power_Time = 0;
			}
		break;

		case 4:         // Three presses
			if(Power_Flag == 2) // Boot completed
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
 * @brie   :WS2812_Power_Display()
 * @note   :display 1..10 leds depending on power level
 **************************************************/
static void WS2812_Power_Display(uint8_t brightness)
{
	uint8_t numleds = 11 - Power_Display_Flag;
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	// 20% and below: red
	// 40% and below: yellow
	// > 40% white
	r = brightness;
	if (numleds > 2)
		g = brightness;
	if (numleds > 4)
		b = brightness;
	
	if (Power_Display_Flag > 0) {
		WS2812_Set_AllColours(1, numleds, r, g, b);
	}
	else {
		WS2812_Set_AllColours(5, 6, brightness, 0, brightness);
	}
	WS2812_Refresh();
}

/**************************************************
 * @brie   : WS2812_VESC()
 * @note   : Display VESC status
 **************************************************/
static void WS2812_VESC(void)
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
			
		  if (data.state != RUNNING_WHEELSLIP) {
				uint8_t brightness = lcmConfig.isSet ? lcmConfig.statusbarBrightness : WS2812_Measure;

				if (Power_Display_Flag > 7) {
					// Voltage below 30%?
					// Display 1/2 red dots at full brightness above anything else
					WS2812_Power_Display(255);
				}
				else if (data.dutyCycleNow > 90) {
					WS2812_Set_AllColours(1, 10,brightness,0,0);
				}
				else if (data.dutyCycleNow > 85) {
					WS2812_Set_AllColours(1, 9,brightness,0,0);
				}
				else if (data.dutyCycleNow > 80) {
					WS2812_Set_AllColours(1, 8,brightness,brightness/2,0);
				}
				else if (data.dutyCycleNow > 70) {
					WS2812_Set_AllColours(1, 7,brightness/3,brightness/3,0);
				}
				else if (data.dutyCycleNow > 60) {
					WS2812_Set_AllColours(1, 6,0,brightness/3,0);
				}
				else if (data.dutyCycleNow > 50) {
					WS2812_Set_AllColours(1, 5,0,brightness/4,0);
				}
				else if (Power_Display_Flag > 6) {
					// Voltage below 40%?
					// Display 1/2/3 red dots at full brightness
					WS2812_Power_Display(128);
				}
				else {
					WS2812_Set_AllColours(1, 10,0,0,0);
				}
			}
			else {
					WS2812_Set_AllColours(1, 10,0,0,0);
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
			if (errCode == 0)
				errCode = 1;
			//WS2812_Set_AllColours(9, 10,50,0,0);
		break;
	}
	WS2812_Refresh();
}


/**************************************************
 * @brie   :WS2812_Boot()
 * @note   :Boot Animation
 **************************************************/
void WS2812_Boot(void)
{
	uint8_t i;
	uint8_t num = floor(Power_Time / 100) + 1;
	// Rainbow: uint8_t rgbMap[10][3] = {{255,0,0}, {255,127,0}, {255,255,0}, {127,255,0}, {0,255,0}, {0,255,127}, {0,255,255}, {0,127,255}, {0,0,255}, {127,0,255}};
	// Red, White, Blue:
	uint8_t rgbMap[10][3] = {{255,0,0}, {255,0,0}, {255,0,0}, {255,255,255}, {255,255,255}, {255,255,255}, {255,255,255}, {0,0,255}, {0,0,255}, {0,0,255}};

	while (num > 10) {
		num -= 10;
	}
	for (i=0;i<num;i++) {
		// red and green are swapped!
		WS2812_Set_Colour(i,rgbMap[i][1] >> 1,rgbMap[i][0] >> 1,rgbMap[i][2] >> 1);
	}

	for (i = num; i < 10; i++) {
		WS2812_Set_Colour(i,rgbMap[i][1] >> 4,rgbMap[i][0] >> 4,rgbMap[i][2] >> 4);
	}

	WS2812_Refresh();
}

void WS2812_Shutdown(void)
{
	uint8_t brightness = 100;
	int num = 10 - floor(Power_Time / 100);
	if (num < 1) {
		num = 1;
	}
	WS2812_Set_AllColours(num, num, brightness / (11 - num), 0, 0);
	WS2812_Refresh();
}

uint8_t status_brightness = 1;
/**************************************************
 * @brie   : WS2812_Calc_Bri()
 * @note   : Pulsate brightness
 * @param  : times 1 means 200ms
**************************************************/
static uint8_t WS2812_Calc_Bri(uint8_t cnt)
{	
	if(cnt < 50)
	{
		status_brightness++;
	}
	else
	{
		status_brightness--;
	}
	
	if(status_brightness < 1)
	{
		status_brightness = 1;
	}
	
	if(status_brightness > 50)
	{
		status_brightness = 50;
	}
	
	return status_brightness;
}

/**************************************************
 * @brie   :WS2812_Charge()
 * @note   :Power LED display while charging
 **************************************************/
static void WS2812_Charge(void)
{
	static uint8_t cnt = 0;
	WS2812_Power_Display(WS2812_Calc_Bri(cnt));
	cnt++;
	if(cnt == 100)
	{
		cnt = 0;
	}
	
	WS2812_Refresh();
}	

static void WS2812_Disabled(void)
{
	int brightness = WS2812_Measure;
	if (brightness < 20)
		brightness = 20;

	// 2 red LEDs in the center
	WS2812_Set_AllColours(5, 6, brightness, 0, 0);
	WS2812_Refresh();
}

// Idle animation:
static void WS2812_Idle(void)
{
	static int cnt = 0;
	cnt++;
	if(cnt == 8 * 512)
	{
		cnt = 0;
	}
	if ((cnt % 80) == 0) {
		int r, g, b;
		int div = cnt >> 3; // fast div by 8
		int idx = div % 10;
		r = div; if (r > 255) r = 0;
		g = -128 + div; if (g < 0) g = 0; if (g > 255) g = 0;
		b = 256 + div; if (b < 0) b = 0; if (b > 255) b = 0;
		WS2812_Set_AllColours(idx, idx, r, g, b);
		WS2812_Refresh();
	}
}

static void WS2812_Handtest(void)
{
	static int pulsate = 0;
	int brightness = WS2812_Measure;
	if (brightness < 20)
		brightness = 20;
	pulsate++;
	if (pulsate > 50)
		pulsate = 0;

	// 4 LEDs in the center
	WS2812_Set_AllColours(4, 7, brightness, pulsate, 0);
	if(ADC1_Val > 2.0)
		WS2812_Set_Colour(0, 0, 0, brightness);
	if(ADC2_Val > 2.0)
		WS2812_Set_Colour(9, 0, 0, brightness);

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
	uint8_t i;

	if(WS2812_Counter < 20) // 20ms refresh period
	{
		return;
	}
	WS2812_Counter = 0;
	
	if(Charge_Flag == 3) // Battery fully charged
	{
		WS2812_Set_AllColours(1,10,100,150,100);	// white with a green tint
		WS2812_Refresh();
		return;
	}
	if(Charge_Flag == 2) // Charge display pattern (pulsating led)
	{
		WS2812_Charge();
		return;
	}

	if (WS2812_Display_Flag == 3) {
		WS2812_Shutdown();
		return;
	}

	if(Power_Flag == 0 || (Power_Flag == 3 && Charge_Flag == 0))
	{
		// Board is off
		WS2812_Set_AllColours(1,10,0,0,0);
		WS2812_Refresh();
		WS2812_Display_Flag = 0;
		WS2812_Flag = 0;
		Power_Display_Flag = 0;
		return;
	}
	
	if(Power_Flag == 1)
	{
		if (data.state == DISABLED) {
			// 2 red LEDs in the center
			WS2812_Disabled();
		}
		else {
			WS2812_Boot();
		}
		return;
	}
	
	if (Power_Flag > 2) {
		WS2812_Refresh();
		return;
	}
	
	// Power Flag must be 2, aka board is ready or running
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

	if (data.state == DISABLED) {
		WS2812_Disabled();
	}
	else if (data.isHandtest) {
		WS2812_Handtest();
	}
	else {
		if(WS2812_Display_Flag == 1)  // I think this is when the board is idle, no footpads pressed
		{
			//if (lcmConfig.isSet && ((lcmConfig.statusbarMode & 0x2) != 0))
			//	WS2812_Idle();	// Idle animation
			//else
			WS2812_Power_Display(WS2812_Measure);	// Display power level
			WS2812_Refresh();
		}
		else
		{
			WS2812_VESC();
		}
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

	if (Power_Flag == 4) {
		if(Power_Time > VESC_SHUTDOWN_TIME)
		{
			Power_Flag = 3;
		}
	}
	
	if(power_flag_last == Power_Flag && Power_Flag != 1)
	{
		return;
	}
	power_flag_last = Power_Flag;
	
	switch(Power_Flag)
	{
		case 1://VESC Power On
			PWR_ON;
			switch(power_step)
			{
				case 0:
					Power_Time = 0;
					power_step = 1;
				break;
				
				case 1:
					if(Power_Time > VESC_BOOT_TIME)
					{
						Power_Flag = 2; // Boot completed
						Gear_Position = 1; // The default setting is 1st gear after power-on.
						Buzzer_Flag = 2;    // The default buzzer sounds when powering on
						power_step = 0;
						WS2812_Display_Flag = 1;
					}
				break;
			}
			
		break;	

		case 3:// VESC is shut down (either auto-shutdown or button press)
			WS2812_Display_Flag = 0;
			PWR_OFF 
		break;

		case 4:// New Power state for shutdown sequence
			WS2812_Display_Flag = 3;
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
 * @brie   :Charge_Task()
 * @note   :Check for charge start/end conditions
 **************************************************/
void Charge_Task(void)
{
	static uint8_t charge_step = 0; 

	if(Charge_Flag > 0)
	{
		if(V_I == 0 && Charge_Time > 150)
		{
			if(Charge_Current < CHARGE_CURRENT && Charge_Current > 0)
			{
				Charge_Flag = 3;
				Shutdown_Cnt++;
				if(Shutdown_Cnt>10)
				{
					Charge_Flag = 0;
					Charge_Voltage = 0;
					//Charge_Current = 0;
					Charger_Detection_1ms = 0;
					charge_step = 0;
					Shutdown_Cnt = 0;
					Charge_Time = 0;
					V_I = 1;
					LED1_ON; // Use ADC3 to measure charge voltage
					CHARGE_OFF;
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
	}
	else //	Charge_Flag == 0
	{
		charge_step = 0;
		if(Charge_Voltage > CHARGING_VOLTAGE)// && (Charge_Current > 0.1))
		{
			if(Charger_Detection_1ms > CHARGER_DETECTION_DELAY)
			{
				if (Charge_Flag != 2)
					Charge_Flag = 1;
				WS2812_Display_Flag = 0;
			}
		}
		else {
			Charger_Detection_1ms = 0;
			return;
		}
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
			CHARGE_ON;
			Charge_Flag = 2;
		    charge_step = 3;
			//Power_Flag = 1;	// Boot the VESC
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
				LED1_ON; // Use ADC3 to measure charge voltage
				charge_step = 5;
			}
		break;
			
		case 5:
			if(Charge_Time > DETECTION_SWITCH_TIME) 
			{
				V_I = 0;
				Charge_Time = 0;
				LED1_OFF; // Use ADC3 to measure charge current
				charge_step = 4;
			}		
		break;
			
		
		default:
			if (errCode == 0)
				errCode = 3;
			
		break;
		
	}
}

void Headlights_Task(void)
{
	static bool isForward = false;

	if(Power_Flag != 2) // Lights off 
	{
		LED_B_OFF;
		LED_F_OFF;
		TIM_SetCompare2(TIM1,0);
		Current_Headlight_Brightness = 0;
		return;
	}

	if ((data.state < RUNNING_FLYWHEEL) || (ADC1_Val > 2) || (ADC2_Val > 2)) {
		if (Current_Headlight_Brightness < lcmConfig.headlightBrightness) {
			Current_Headlight_Brightness++;
		}
		else if (Current_Headlight_Brightness > lcmConfig.headlightBrightness) {
			Current_Headlight_Brightness--;
		}

		if (isForward != data.isForward) {
			Current_Headlight_Brightness = 0;
			isForward = data.isForward;
		}
		if (data.isForward)
		{ // FORWARD
			LED_F_OFF;
			LED_B_ON;
		}
		else
		{ // BACKWARD
			LED_B_OFF;
			LED_F_ON;
		}

		if (lcmConfig.isSet) {
			TIM_SetCompare2(TIM1,9999 - Current_Headlight_Brightness*39);
		}
		else {
			switch(Gear_Position)
			{
				case 1:
					// OFF
					TIM_SetCompare2(TIM1,9999);
				break;
				
				case 2:
					// MEDIUM
					TIM_SetCompare2(TIM1,4000);
				break;
				
				case 3:
					// HIGH
					TIM_SetCompare2(TIM1,0);
				break;
				
				default:
					if (errCode == 0)
						errCode = 4;
					
				break;
			}
		}
	}
	else {
		// For now ZERO lights when stopped
		LED_F_OFF;
		LED_B_OFF;
		TIM_SetCompare2(TIM1,9999);
		Current_Headlight_Brightness = 0;
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
	static uint8_t alternate = 0;
	uint8_t result;

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
		data.isForward = true;

		lcmConfigReset();

		usart_step = 0;
		
		return;
	}
	
	switch(usart_step)
	{
		case 0:
			// Try the custom app command for the first 2 seconds then fall back to generic GET_VALUES
			if ((data.floatPackageSupported == false) && (Power_Time > VESC_BOOT_TIME * 2))
				Get_Vesc_Pack_Data(COMM_GET_VALUES);
			else {
				if (alternate) {
					Get_Vesc_Pack_Data(COMM_CUSTOM_DEBUG);
				}
				else {
					Get_Vesc_Pack_Data(COMM_CUSTOM_APP_DATA);
				}
			}

			alternate = 1 - alternate;

			usart_step = 1;
		break;
		
		case 1:
			if(VESC_RX_Flag == 1)
			{
				VESC_RX_Flag = 0;
				result = Protocol_Parse(VESC_RX_Buff);
				
				Vesc_Data_Ready = (result == 0);
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
 * @brie   :ADC_Task()
 * @note   :Eavluate the 3 ADCs: 2 x sensors and 1 x current/voltage (multiplexed via LED1)
 **************************************************/
void ADC_Task(void)
{
	static uint8_t adc_step = 0;
	static uint16_t adc_charge_sum_ave = 0;
	static uint16_t adc1_val_sum_ave = 0;
	static uint16_t adc2_val_sum_ave = 0;
	
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
				
				if(V_I == 0)
				{
					if(Charge_Time>100)
					{
						Charge_Current = (float)(-0.008056640625*adc_charge_sum_ave+16.5);
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
			
		break;
			
	  default:
			
		break;
	}
}

/**************************************************
 * @brie   :VESC_State_Task()
 * @note   :proces VESC state when power is on and we're not charging
 **************************************************/
void VESC_State_Task(void)
{
	if ((Charge_Flag > 0) || (Power_Flag != 2) || !Vesc_Data_Ready)
		return;

	Vesc_Data_Ready = false;
		
	// Not charging? Get voltage from VESC
	CheckPowerLevel((data.inpVoltage+1)/BATTERY_STRING);

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
	
	if(data.rpm<0)
	{
		data.rpm = -data.rpm;
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
				Buzzer_Frequency = 100;
			}
		}
		else {
			Buzzer_Frequency = 0;

			if(ADC1_Val < 2.0 && ADC2_Val <2.0)
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
	
	// No movement and no ADCs? Shutdown after timeout (10-30min)
	if(ADC1_Val > 2.0 || ADC2_Val > 2.0 || data.rpm > 1000)
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
			Power_Flag = 4;
			Power_Time = 0;
		}
	}

	if(((Shutdown_Time_M > 0) || (Shutdown_Time_S >= 10000)) && (lcmConfig.boardOff > 0))
	{
		// After 10 seconds of idle we allow the board to be shut down via app
		Power_Flag = 4;
		Power_Time = 0;
	}
}
