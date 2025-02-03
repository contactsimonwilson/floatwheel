#include "key_app.h"

/**************************************************
 * @brie  :KEY_Init()
 * @note  :KEY initialization [KEY��ʼ��]
 * @param :none [��]
 * @retval:none [��]
 **************************************************/
void KEY_Task(void)
{
	if(KEY1_State == 0)  //Charger power button does not work [��������簴����������]
	{
		return;
	}
	
	switch(KEY1_State)
	{
		case 1:  	//Click [����]
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
		
		case 2:		//Double Click [˫��]
		
		break;
		
		case 3:		//Long Press [����]
			if(Flag.Power == 0)
			{
				Flag.Key_Boot = 1;
				Flag.Power = 1;
			}
			else if(Flag.Charger_ON == 0) //Turn on the charger to charge, but press the button to not shut down [�����������磬�������ػ�]
			{
				Flag.Power = 3;
			}
		break;
		
		case 4:		//Triple Press [����]
			
		break;
		
	}
	KEY1_State = 0;
}

