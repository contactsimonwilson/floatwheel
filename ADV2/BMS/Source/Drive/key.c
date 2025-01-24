#include "key.h"

/*
 *	KEY1_State = 0  按键没按下
 *	KEY1_State = 1  单击
 *	KEY1_State = 2  双击
 *  KEY1_State = 3  长按
 *  KEY1_State = 4  三按
 */
uint8_t KEY1_State = 0;  

/*
	LED -> PA0
*/

/**************************************************
 * @brie  :KEY_Init()
 * @note  :KEY初始化
 * @param :无
 * @retval:无
 **************************************************/
void KEY_Init(void)
{
	GPIO_InitType GPIO_InitStructure;

	GPIO_InitStruct(&GPIO_InitStructure);
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA,ENABLE);

	GPIO_InitStructure.Pin          = GPIO_PIN_0;	
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_Pull_Down;
    GPIO_InitStructure.GPIO_Mode  	= GPIO_Mode_Input;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**************************************************
 * @brie   :KEY1_Scan()
 * @note   :KEY1扫描
 * @param  :无
 * @retval :无
 **************************************************/
void KEY1_Scan(void)
{
	static uint8_t   key1_st= 0;
	static uint16_t  key1_cnt = 0;
	static uint16_t  key1_cnt_2 = 0;
	static uint16_t  key1_num = 0;
	
	switch(key1_st)
	{
		case 0:
			
			if(KEY1 == 1)
			{
				key1_cnt++;
				if(key1_cnt == 20) //消抖
				{
					key1_cnt = 0;
					key1_st = 1;
				}
			}
			else
			{
				key1_cnt = 0;
				key1_cnt_2 = 0;
			}
			
		break;
		
		case 1:
			key1_cnt++;   
		    key1_cnt_2++;
			if(KEY1 == 0) //按键已经抬起 最少是个单击 
			{
				key1_num++;
				key1_st = 2;
				key1_cnt = 0;
				
			}
			else if (key1_cnt > 1500)  //长按有效
			{
				key1_cnt = 0;
				key1_st = 3;
				
				KEY1_State = 3;
			}
			
		break;
		
		case 2:
			key1_cnt_2++;
			
			if(key1_cnt_2 < 500) //250ms内看按键按了多少次
			{
				if(KEY1 == 1)
				{
					key1_cnt++;
					if(key1_cnt == 2) //消抖
					{
						key1_cnt = 0;
						key1_st = 1;
					}
				}
				else
				{
					key1_cnt = 0;
				}
			}
			else
			{
				key1_cnt_2 = 0;
				key1_st = 4;
			}
			
		break;
		
		case 3:
			
			if(KEY1 == 0) //长按完等待按键抬起
			{
				key1_st = 0;
			}
			
		break;
			
		case 4:	
			
			switch(key1_num)
			{
				case 1: //单击
					KEY1_State = 1;
				break;
				
				case 2: //双击
					KEY1_State = 2;
				break;
				
				case 3: //三击
					KEY1_State = 4;
				break;
				//四击 五击 ...自行添加
				
				default: //key3_num的值 可能不是1 2 3 最好加这一句 预防bug
					
				break;
			}
			
			key1_num = 0;
			key1_st = 0;
		break;
	}	
}

