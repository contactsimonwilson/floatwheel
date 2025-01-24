#include "key_app.h"

/**************************************************
 * @brie  :KEY_Init()
 * @note  :KEY初始化
 * @param :无
 * @retval:无
 **************************************************/
void KEY_Task(void)
{
	if(KEY1_State == 0)  //充电器供电按键不起作用
	{
		return;
	}
	
	switch(KEY1_State)
	{
		case 1:  	//单击
//			if(Flag.Power == 4)
//			{
//				NVIC_SystemReset();
//			}
			if(Flag.Power == 0 || Flag.Power == 4)
			{
				LED_Flicker_Time = 500;
				Flag.Key_Boot = 1;
				Flag.Power = 1;
			}
		break;
		
		case 2:		//双击	
		
		break;
		
		case 3:		//长按
			if(Flag.Power == 0)
			{
				Flag.Key_Boot = 1;
				Flag.Power = 1;
			}
			else if(Flag.Charger_ON == 0) //开机充电器充电，按键不关机
			{
				Flag.Power = 3;
			}
		break;
		
		case 4:		//三按
			
		break;
		
	}
	KEY1_State = 0;
}

