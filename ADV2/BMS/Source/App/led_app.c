#include "led_app.h"

void LED_Task(void)
{
	if(Software_Counter_1ms.LED >= LED_Flicker_Time)
	{
		Software_Counter_1ms.LED = 0;
		LED_FLIP;
	}
}

