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

uint32_t dispcnt = 123456;  /*LCD display data*/
uint8_t  dispstr[8] = {0,};  /*LCD display buffer*/

uint8_t RTC_wakeup_flag = 0;    /*RTC auto wakeup flag*/
uint8_t UDD_wakeup_flag = 0;    /*LCD UDD wakeup flag*/
uint8_t udd_wait_type = UDD_WAIT_INT;   /*LCD refresh wait type,interrupt or block*/

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
 * @brief  Config the LCD interrupt.
 * @param  None
 * @retval None
 */
void LCD_ConfigInt(void)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    
    /* Clear the LCD interrupt flag in both LCD and EXTI module */
    __LCD_CLEAR_FLAG(LCD_FLAG_UDD_CLEAR|LCD_FLAG_SOF_CLEAR);
    EXTI_ClrStatusFlag(EXTI_LINE26);

    /* Config the LCD interrupt througn EXTI line 26 */
    EXTI_InitStructure.EXTI_Line = EXTI_LINE26;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
    
    /* Enable the LCD interrupt in NVIC */
    NVIC_InitStructure.NVIC_IRQChannel                   = LCD_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    /* Enable the LCD UDD interrupt in LCD module */
    __LCD_ENABLE_IT(LCD_IT_UDD);
}

/**
 * @brief  Change the data to LCD display string format.
 * @param  pStr: Pointer to the result buffer for LCD display string, maximum length is 6 
 * @param  data: The data to be display
 * @retval None
 */
void Data2Str(uint8_t *pStr, uint32_t data) /*max str data len = 6*/
{
    uint32_t i,tdata = data;
    
    for(i=0;i<6;i++)
    {
        pStr[5-i] = (tdata % 10) + '0';
        tdata /= 10;
    }
    
    pStr[6] = '\0';
}

/**
 * @brief  Config the RTC auto wakeup interrupt.
 * @param  None 
 * @retval None
 */
void RTC_ConfigWakeUp(void)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    
    /* LCD is inited,RTC clock is set as LSI 40KHz*/
    /* Config the RTC auto wakeup time as about 1 second */
    RTC_ConfigWakeUpClock(RTC_WKUPCLK_RTCCLK_DIV16);
    RTC_SetWakeUpCounter(2500);
    
    /* Config the RTC auto wakeup interrupt througn EXTI line 20 */
    EXTI_ClrITPendBit(EXTI_LINE20);
    EXTI_InitStructure.EXTI_Line = EXTI_LINE20;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
    
    /* Enable the RTC auto wakeup interrupt in NVIC */
    NVIC_InitStructure.NVIC_IRQChannel                   = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Enable the RTC auto wakeup interrupt in RTC module */
    RTC_ConfigInt(RTC_INT_WUT,ENABLE);
    
    /* Enable the RTC auto wakeup function */
    RTC_EnableWakeUp(ENABLE);
}
/**
 * @brief  Main program.
 */
int main(void)
{
    /* Config NVIC priority group */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    BSP_LCD_GLASS_Init(); /*Initialize the LCD.*/
    
    GPIO_Init();    /*Initialize GPIO for LED and key*/
    Delay(SystemCoreClock>>6);  /*Short delay*/

    if((KEY_PORT->PID & KEY_PIN) == KEY_PIN)    /*If KEY3 is pressed, LCD UDD interrupt is not used*/
    {
        udd_wait_type = UDD_WAIT_BLOCK;
        while(KEY_PORT->PID & KEY_PIN);         /* Wait until KEY3 is released */
    }
    else                                        /*If KEY3 is not pressed,LCD UDD interrupt is used(default)*/
    {
        LCD_ConfigInt();
        udd_wait_type = UDD_WAIT_INT;
    }
    
    /*Just for user debug*/
    #ifdef LCD_LOWPOWER_DEBUG
        DBG->CTRL |= DBG_CTRL_SLEEP|DBG_CTRL_STOP|DBG_CTRL_STDBY;
    #endif

    /*LCD display default string:123456*/
    Data2Str(dispstr,dispcnt);              /*Change the display data format to LCD display string */
    BSP_LCD_GLASS_DisplayString(dispstr,5); /*Write the LCD data register*/
    
    if(UDD_WAIT_BLOCK == udd_wait_type) /*If LCD UDD interrupt is not used,wait until refresh done*/
    {
        LCD_UpdateDisplayRequest();
    }
    else                                /*If LCD UDD interrupt is used,just set the UDR flag,no need to wait*/
    {
        __LCD_CLEAR_FLAG(LCD_FLAG_UDD_CLEAR);
        __LCD_UPDATE_REQUEST();
    }
    
    Delay(SystemCoreClock*2);       /* Long delay */
    RTC_ConfigWakeUp();             /* Enable RTC auto wakeup */

#if     (defined(N32L436MBL_EVB_V1_0))
    __LCD_DISPLAY_IN_STOP2();
#endif
    
    while(1)
    {
        MCU_RUN_LED_OFF;            /*Turn off MCU status LED D16 */
        PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI,PWR_CTRL3_RAM1RET|PWR_CTRL3_RAM2RET);  /* Enter STOP2 mode */
        MCU_RUN_LED_ON;             /*Turn on MCU status LED D16 */
        
        if(UDD_wakeup_flag)     /*If MCU is wake up by LCD UDD interrupt,just clear the flag */
        {
            UDD_wakeup_flag = 0;
            continue;
        }
        
        if(RTC_wakeup_flag)     /*If MCU is wake up by RTC interrupt, refresh the display data */
        {
            RTC_wakeup_flag = 0;
        }
        else
        {
            continue;
        }

        dispcnt++;                  /* Update the display data */
        Data2Str(dispstr,dispcnt);  /* Change the display data format to LCD display string */
        
        if(RESET == (__LCD_GET_FLAG(LCD_FLAG_UDD))) /*If LCD refresh is not done,can not write LCD data register,generally do not happen */
        {
            continue;
        }

        BSP_LCD_GLASS_DisplayString(dispstr,5); /*Write the LCD data register*/ 
        if(UDD_WAIT_BLOCK == udd_wait_type)
        {
            LCD_UpdateDisplayRequest();         /*If LCD UDD interrupt is not used,wait until refresh done*/
        }
        else                                    /*If LCD UDD interrupt is used,just set the UDR flag,no need to wait*/
        {
            __LCD_CLEAR_FLAG(LCD_FLAG_UDD_CLEAR);
            __LCD_UPDATE_REQUEST();
        }
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
    // printf("%s\r\n%s\r\n",expr,file);
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT


/******************************************************************/
/**
 * @}
 */
