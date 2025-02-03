#include "key_app.h"

/**************************************************
 * @brie  :KEY_Init()
 * @note  :KEY initialization [KEY初始化]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void KEY_Task(void)
{
	if(KEY1_State == 0)  //Charger power button does not work [充电器供电按键不起作用]
	{
		return;
	}
	
	switch(KEY1_State)
	{
		case 1:  	//Click [单击]
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
		
		case 2:		//Double Click [双击]
		
		break;
		
		case 3:		//Long Press [长按]
			if(Flag.Power == 0)
			{
				Flag.Key_Boot = 1;
				Flag.Power = 1;
			}
			else if(Flag.Charger_ON == 0) //Turn on the charger to charge, but press the button to not shut down [开机充电器充电，按键不关机]
			{
				Flag.Power = 3;
			}
		break;
		
		case 4:		//Triple Press [三按]
			
		break;
		
	}
	KEY1_State = 0;
}

