#include "key_app.h"

/**************************************************
 * @brie  :KEY_Init()
 * @note  :KEY��ʼ��
 * @param :��
 * @retval:��
 **************************************************/
void KEY_Task(void)
{
	if(KEY1_State == 0)  //��������簴����������
	{
		return;
	}
	
	switch(KEY1_State)
	{
		case 1:  	//����
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
		
		case 2:		//˫��	
		
		break;
		
		case 3:		//����
			if(Flag.Power == 0)
			{
				Flag.Key_Boot = 1;
				Flag.Power = 1;
			}
			else if(Flag.Charger_ON == 0) //�����������磬�������ػ�
			{
				Flag.Power = 3;
			}
		break;
		
		case 4:		//����
			
		break;
		
	}
	KEY1_State = 0;
}

