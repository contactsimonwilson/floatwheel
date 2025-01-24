/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include "bsp_gpio.h"
#include "bsp_lcd.h"
#include "bsp_usart.h"

/**
 * @brief  Inserts a delay time.
 * @param count specifies the delay time length.
 */
void Delay(uint32_t count)
{
    for (; count > 0; count--)
        ;
}


/**
 * @brief  Enable and enter sleep mode.
 * @param  None
 * @retval None
 */
void LCD_ConfigInt(void)
{
    EXTI_InitType EXTI_InitStructure;

    EXTI_InitStructure.EXTI_Line = EXTI_LINE26;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    NVIC_InitType NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel                   = LCD_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    __LCD_CLEAR_FLAG(LCD_FLAG_SOF_CLEAR);
    __LCD_ENABLE_IT(LCD_IT_SOF);
}

/**
 * @brief  Main program.
 */
int main(void)
{
    /* Init usart port for debug */
    Debug_USART_Config();
    printf("LCD demo!\r\n");
    
    /* Config NVIC priority group */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    /* Init the peripheral */
    BSP_LCD_GLASS_Init(); // Initialize glass LCD.
    Key_GPIO_Init();
    
    while (1)   /* Test loop */
    {
        /*Show all char and mark on LCD*/
        BSP_LCD_GLASS_ShowAll();
        Delay(SystemCoreClock>>LONG_DELAY_TIME_SHIFT);

        /*Clear all*/
        BSP_LCD_GLASS_Clear();
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        
        /*Show repair mark*/
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_T1_REPAIR,0);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);

        /*Show battery level*/
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_W1_BATLEVEL_OFF,LCD_MARK_T1_REPAIR);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_W2_BATLEVEL_1_4,0);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_W3_BATLEVEL_1_2,0);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_W4_BATLEVEL_3_4,0);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_W5_BATLEVEL_FULL,0);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        
        /*Show signal level*/
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_L1_SIGNAL_LEVEL1,
                                 LCD_MARK_W1_BATLEVEL_OFF
                                |LCD_MARK_W2_BATLEVEL_1_4
                                |LCD_MARK_W3_BATLEVEL_1_2
                                |LCD_MARK_W4_BATLEVEL_3_4
                                |LCD_MARK_W5_BATLEVEL_FULL);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_L2_SIGNAL_LEVEL2,0);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_L3_SIGNAL_LEVEL3,0);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_L4_SIGNAL_LEVEL4,0);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        
        /*Show double point one by one*/
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_COL1_LITTLE_COL,
                                 LCD_MARK_L1_SIGNAL_LEVEL1
                                |LCD_MARK_L2_SIGNAL_LEVEL2
                                |LCD_MARK_L3_SIGNAL_LEVEL3
                                |LCD_MARK_L4_SIGNAL_LEVEL4);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_COL2_BIG_COL_1ST,LCD_MARK_COL1_LITTLE_COL);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_COL3_BIG_COL_2ND,LCD_MARK_COL2_BIG_COL_1ST);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);

        /*Show the unit one by one*/
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_S1_UNIT_MV,LCD_MARK_COL3_BIG_COL_2ND);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_S2_UNIT_NM,LCD_MARK_S1_UNIT_MV);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_S3_UNIT_KG,LCD_MARK_S2_UNIT_NM);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_S4_UNIT_G,LCD_MARK_S3_UNIT_KG);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_S5_UNIT_MM,LCD_MARK_S4_UNIT_G);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_S6_UNIT_UE,LCD_MARK_S5_UNIT_MM);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_S7_UNIT_KPA,LCD_MARK_S6_UNIT_UE);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_S8_UNIT_MPA,LCD_MARK_S7_UNIT_KPA);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_ConfigMark(LCD_MARK_S9_UNIT_OC,LCD_MARK_S8_UNIT_MPA);
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        
        /*Clear all*/
        BSP_LCD_GLASS_Clear();
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        
        /*Show the num in big char*/
        BSP_LCD_GLASS_DisplayString((uint8_t*)"123456",5);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"7890  ",5);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        
        /*Show the letter in big char*/
        BSP_LCD_GLASS_DisplayString((uint8_t*)"abcdef",5);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"ghijln",5);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"opqrtu",5);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        
        /*Clear all*/
        BSP_LCD_GLASS_Clear();
        Delay(SystemCoreClock>>SHORT_DELAY_TIME_SHIFT);
        
        /*Show the num in little char*/
        BSP_LCD_GLASS_DisplayString((uint8_t*)"1234",1);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"5678",1);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"90  ",1);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        
        /*Show the letter in little char*/
        BSP_LCD_GLASS_DisplayString((uint8_t*)"abcd",1);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"efgh",1);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"ijln",1);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"opqr",1);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"tu  ",1);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);
        
        /*Show a string in both little and big char*/
        BSP_LCD_GLASS_DisplayString((uint8_t*)"19:28123.45L",1);
        Delay(SystemCoreClock>>MIDDLE_DELAY_TIME_SHIFT);

    #ifdef LCD_LOWPOWER_DEBUG
        DBG->CTRL |= DBG_CTRL_SLEEP|DBG_CTRL_STOP|DBG_CTRL_STDBY;
    #endif

    #ifdef LCD_LOWPOWER_TEST
        BSP_LCD_GLASS_Clear();

      #if (LCD_LOW_POWER_MODE & LCD_LOWPOWER_WAKEUP)
        LCD_ConfigInt();
      #endif

      #if (LCD_LOW_POWER_MODE & LCD_LOWPOWER_SLEEP)
        BSP_LCD_GLASS_DisplayString((uint8_t*)"INTOSLEEP ",1);
        Delay(SystemCoreClock>>LONG_DELAY_TIME_SHIFT);
        
        PWR_EnterSLEEPMode(0,PWR_SLEEPENTRY_WFI);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"QUITSLEEP  ",1);
        Delay(SystemCoreClock>>LONG_DELAY_TIME_SHIFT);
      #endif

      #if (LCD_LOW_POWER_MODE & LCD_LOWPOWER_LSLEEP)
        PWR_EnterLowPowerRunMode();
        SystemCoreClockUpdate();
        BSP_LCD_GLASS_Init();
        BSP_LCD_GLASS_DisplayString((uint8_t*)"INTOLORUN   ",1);
        Delay(SystemCoreClock>>LONG_DELAY_TIME_SHIFT);
        
        BSP_LCD_GLASS_DisplayString((uint8_t*)"INTOLSLEEP",1);
        Delay(SystemCoreClock>>LONG_DELAY_TIME_SHIFT);
        
        PWR_EnterSLEEPMode(0,PWR_SLEEPENTRY_WFI);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"QUITLSLEEP",1);
        Delay(SystemCoreClock>>LONG_DELAY_TIME_SHIFT);
      #endif
        
      #if (LCD_LOW_POWER_MODE & LCD_LOWPOWER_STOP2)
        BSP_LCD_GLASS_DisplayString((uint8_t*)"INTOSTOP2 ",1);
        Delay(SystemCoreClock>>LONG_DELAY_TIME_SHIFT);
        
        __LCD_DISPLAY_IN_STOP2();
        PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI,PWR_CTRL3_RAM1RET|PWR_CTRL3_RAM2RET);
        BSP_LCD_GLASS_DisplayString((uint8_t*)"QUITSTOP2 ",1);
        Delay(SystemCoreClock>>LONG_DELAY_TIME_SHIFT);
      #endif
        
    #endif
    }
}

/******************************************************************/

/**
 * @brief Assert failed function by user.
 * @param file The name of the call that failed.
 * @param line The source line number of the call that failed.
 */
#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT


/******************************************************************/
/**
 * @}
 */
