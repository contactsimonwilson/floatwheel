#include <stdio.h>
#include <stdint.h>
#include "log.h"
#include "n32l40x_rtc.h"
#include "User_RTC_Config.h"
#include "User_Delay_Config.h"

RTC_DateType  RTC_DateStructure;
RTC_DateType  RTC_DateDefault;
RTC_TimeType  RTC_TimeStructure;
RTC_TimeType  RTC_TimeDefault;
RTC_InitType  RTC_InitStructure;
RTC_AlarmType RTC_AlarmStructure;
RTC_AlarmType RTC_AlarmDefault;
uint32_t SynchPrediv, AsynchPrediv;

/**
 * @brief  Display the current alarm time on the Hyperterminal.
  * @param RTC_Alarm specifies the alarm to be operation.
 *   This parameter can be one of the following values:
 *     @arg RTC_A_ALARM to select Alarm A.
 *     @arg RTC_B_ALARM to select Alarm B.
 */
void RTC_AlarmShow(uint8_t AlarmX)
{
    /* Get the current Alarm */
    if (AlarmX == 0x01)
        RTC_GetAlarm(RTC_FORMAT_BIN, RTC_A_ALARM, &RTC_AlarmStructure);
    else
        RTC_GetAlarm(RTC_FORMAT_BIN, RTC_B_ALARM, &RTC_AlarmStructure);
    printf("\n\r //=========== Current Alarm Display ==============// \n\r");
    printf("\n\r The current alarm is :  %02u:%02u:%02u \n\r",\
           RTC_AlarmStructure.AlarmTime.Hours,\
           RTC_AlarmStructure.AlarmTime.Minutes,\
           RTC_AlarmStructure.AlarmTime.Seconds);
}

/**
 * @brief  Display the current Date on the Hyperterminal.
 */
void RTC_DateShow(void)
{
    /* Get the current Date */
    RTC_GetDate(RTC_FORMAT_BIN, &RTC_DateStructure);
    log_info("\n\r //=========== Current Date Display ==============// \n\r");
    log_info("\n\r The current date (WeekDay-Date-Month-Year) is :  %02u-%02u-%02u-%02u \n\r",\
             RTC_DateStructure.WeekDay,\
             RTC_DateStructure.Date,\
             RTC_DateStructure.Month,\
             RTC_DateStructure.Year);
}

/**
 * @brief  Display the current time on the Hyperterminal.
 */
void RTC_TimeShow(void)
{
    /* Get the current Time and Date */
    RTC_GetTime(RTC_FORMAT_BIN, &RTC_TimeStructure);
    log_info("\n\r //============ Current Time Display ===============// \n\r");
    log_info("\n\r The current time (Hour-Minute-Second) is :  %02u:%02u:%02u \n\r",\
             RTC_TimeStructure.Hours,\
             RTC_TimeStructure.Minutes,\
             RTC_TimeStructure.Seconds);
    /* Unfreeze the RTC DAT Register */
    (void)RTC->DATE;
}

/**
 * @brief  RTC initalize default value.
 */
void RTC_DateAndTimeDefaultVale(void)
{ // Date
    RTC_DateDefault.WeekDay = 3;
    RTC_DateDefault.Date    = 20;
    RTC_DateDefault.Month   = 11;
    RTC_DateDefault.Year    = 19;
    // Time
    RTC_TimeDefault.H12     = RTC_AM_H12;
    RTC_TimeDefault.Hours   = 4;
    RTC_TimeDefault.Minutes = 22;
    RTC_TimeDefault.Seconds = 30;
    // Alarm
    RTC_AlarmDefault.AlarmTime.H12     = RTC_AM_H12;
    RTC_AlarmDefault.AlarmTime.Hours   = 4;
    RTC_AlarmDefault.AlarmTime.Minutes = 23;
    RTC_AlarmDefault.AlarmTime.Seconds = 00;
    RTC_AlarmDefault.DateWeekMode      = RTC_ALARM_SEL_WEEKDAY_DATE;
}

/**
 * @brief  RTC alarm regulate with the default value.
 * @param RTC_Alarm specifies the alarm to be configured.
 *   This parameter can be one of the following values:
 *     @arg RTC_A_ALARM to select Alarm A.
 *     @arg RTC_B_ALARM to select Alarm B.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC Alarm regulate success
 *          - ERROR: RTC Alarm regulate failed
 */
ErrorStatus RTC_AlarmRegulate(uint32_t RTC_Alarm)
{
    unsigned int tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
    /* Disable the AlarmX */
    RTC_EnableAlarm(RTC_Alarm, DISABLE);
    printf("\n\r //==============Alarm X Settings================// \n\r");
    RTC_AlarmStructure.AlarmTime.H12 = RTC_AM_H12;
    RTC_TimeStructure.H12            = RTC_AM_H12;
    printf("\n\r Please Set Alarm Hours \n\r");
    tmp_hh = RTC_AlarmDefault.AlarmTime.Hours;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_AlarmStructure.AlarmTime.Hours = tmp_hh;
    }
    printf(": %02u\n\r", tmp_hh);
    printf("\n\r Please Set Alarm Minutes \n\r");
    tmp_mm = RTC_AlarmDefault.AlarmTime.Minutes;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_AlarmStructure.AlarmTime.Minutes = tmp_mm;
    }
    printf(": %02u\n\r", tmp_mm);
    printf("\n\r Please Set Alarm Seconds \n\r");
    tmp_ss = RTC_AlarmDefault.AlarmTime.Seconds;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_AlarmStructure.AlarmTime.Seconds = tmp_ss;
    }
    printf(": %02u\n\r", tmp_ss);
    /* Set the Alarm X */
    RTC_AlarmStructure.DateWeekValue = 0x31;
    RTC_AlarmStructure.DateWeekMode = RTC_AlarmDefault.DateWeekMode;
    RTC_AlarmStructure.AlarmMask = RTC_ALARMMASK_WEEKDAY | RTC_ALARMMASK_HOURS | RTC_ALARMMASK_MINUTES;
    /* Configure the RTC Alarm A register */
    RTC_SetAlarm(RTC_FORMAT_BIN, RTC_Alarm, &RTC_AlarmStructure);
    printf("\n\r>> !! RTC Set Alarm_X success. !! <<\n\r");
    if (RTC_Alarm == RTC_A_ALARM)
    {
        /* Enable the RTC Alarm A Interrupt */
        RTC_ConfigInt(RTC_INT_ALRA, ENABLE);
        RTC_AlarmShow(1);
    }
    else
    {
        /* Enable the RTC Alarm B Interrupt */
        RTC_ConfigInt(RTC_INT_ALRB, ENABLE);
        RTC_AlarmShow(2);
    }
    /* Enable the alarm   */
    RTC_EnableAlarm(RTC_Alarm, ENABLE);
    return SUCCESS;
}

/**
 * @brief  RTC date regulate with the default value.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC date regulate success
 *          - ERROR: RTC date regulate failed
 */
ErrorStatus RTC_DateRegulate(void)
{
    unsigned int tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
    log_info("\n\r //=============Date Settings================// \n\r");
    log_info("\n\r Please Set WeekDay (01-07) \n\r");
    tmp_hh = RTC_DateDefault.WeekDay;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.WeekDay = tmp_hh;
    }
    log_info(": %02u\n\r", tmp_hh);
    tmp_hh = 0xFF;
    log_info("\n\r Please Set Date (01-31) \n\r");
    tmp_hh = RTC_DateDefault.Date;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Date = tmp_hh;
    }
    log_info(": %02u\n\r", tmp_hh);
    log_info("\n\r Please Set Month (01-12)\n\r");
    tmp_mm = RTC_DateDefault.Month;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Month = tmp_mm;
    }
    log_info(": %02u\n\r", tmp_mm);
    log_info("\n\r Please Set Year (00-99)\n\r");
    tmp_ss = RTC_DateDefault.Year;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_DateStructure.Year = tmp_ss;
    }
    log_info(": %02u\n\r", tmp_ss);
    /* Configure the RTC date register */
    if (RTC_SetDate(RTC_FORMAT_BIN, &RTC_DateStructure) == ERROR)
    {
        log_info("\n\r>> !! RTC Set Date failed. !! <<\n\r");
        return ERROR;
    }
    else
    {
        log_info("\n\r>> !! RTC Set Date success. !! <<\n\r");
        RTC_DateShow();
        return SUCCESS;
    }
}

/**
 * @brief  RTC time regulate with the default value.
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC time regulate success
 *          - ERROR: RTC time regulate failed
 */
ErrorStatus RTC_TimeRegulate(void)
{
    unsigned int tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
    log_info("\n\r //==============Time Settings=================// \n\r");
    RTC_TimeStructure.H12 = RTC_TimeDefault.H12;
    log_info("\n\r Please Set Hours \n\r");
    tmp_hh = RTC_TimeDefault.Hours;
    if (tmp_hh == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Hours = tmp_hh;
    }
    log_info(": %02u\n\r", tmp_hh);
    log_info("\n\r Please Set Minutes \n\r");
    tmp_mm = RTC_TimeDefault.Minutes;
    if (tmp_mm == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Minutes = tmp_mm;
    }
    log_info(": %02u\n\r", tmp_mm);
    log_info("\n\r Please Set Seconds \n\r");
    tmp_ss = RTC_TimeDefault.Seconds;
    if (tmp_ss == 0xff)
    {
        return ERROR;
    }
    else
    {
        RTC_TimeStructure.Seconds = tmp_ss;
    }
    log_info(": %02u\n\r", tmp_ss);
    /* Configure the RTC time register */
    if (RTC_ConfigTime(RTC_FORMAT_BIN, &RTC_TimeStructure) == ERROR)
    {
        log_info("\n\r>> !! RTC Set Time failed. !! <<\n\r");
        return ERROR;
    }
    else
    {
        log_info("\n\r>> !! RTC Set Time success. !! <<\n\r");
        RTC_TimeShow();
        return SUCCESS;
    }
}

/**
 * @brief  RTC prescaler config.
 */
void RTC_PrescalerConfig(void)
{
    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv  = SynchPrediv;
    RTC_InitStructure.RTC_HourFormat   = RTC_24HOUR_FORMAT;
    /* Check on RTC init */
    if (RTC_Init(&RTC_InitStructure) == ERROR)
    {
        log_info("\r\n //******* RTC Prescaler Config failed **********// \r\n");
    }
}

/**
 * @brief  Configures the RTC Source Clock Type.
 * @param Clk_Src_Type specifies RTC Source Clock Type.
 *   This parameter can be on of the following values:
 *     @arg RTC_CLK_SRC_TYPE_HSE128
 *     @arg RTC_CLK_SRC_TYPE_LSE
 *     @arg RTC_CLK_SRC_TYPE_LSI
 * @param Is_First_Cfg_RCC specifies Is First Config RCC Module.
 *   This parameter can be on of the following values:
 *     @arg true
 *     @arg false
 * @return An ErrorStatus enumeration value:
 *          - SUCCESS: RTC clock configure success
 *          - ERROR: RTC clock configure failed
 */
ErrorStatus RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE Clk_Src_Type, bool Is_First_Cfg_RCC)
{
    uint8_t lse_ready_count=0;
    ErrorStatus Status=SUCCESS;
    /* Enable the PWR clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    /* Allow access to RTC */
    PWR_BackupAccessEnable(ENABLE);
    /* Disable RTC clock */
    RCC_EnableRtcClk(DISABLE);
    User_Delay_init();
    if (RTC_CLK_SRC_TYPE_HSE_DIV32 == Clk_Src_Type)
    {
        log_info("\r\n RTC_ClkSrc Is Set HSE/32! \r\n");
        if (true == Is_First_Cfg_RCC )
        {
            /* Enable HSE */
            RCC_EnableLsi(DISABLE);
            RCC_ConfigHse(RCC_HSE_ENABLE);
            while (RCC_WaitHseStable() == ERROR)
            {
            }
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSE_DIV32);
        }
        else
        {
            RCC_EnableLsi(DISABLE);
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_HSE_DIV32);
            /* Enable HSE */
            RCC_ConfigHse(RCC_HSE_ENABLE);
            while (RCC_WaitHseStable() == ERROR)
            {
            }
        }
        SynchPrediv  = 0x7A0; // 8M/32 = 250KHz
        AsynchPrediv = 0x7F;  // value range: 0-7F
    }
    else if (RTC_CLK_SRC_TYPE_LSE == Clk_Src_Type)
    {
        log_info("\r\n RTC_ClkSrc Is Set LSE! \r\n");
        if (true == Is_First_Cfg_RCC)
        {
            /* Enable the LSE OSC32_IN PC14 */
            RCC_EnableLsi(DISABLE); // LSI is turned off here to ensure that only one clock is turned on
    #if (_TEST_LSE_BYPASS_)
            RCC_ConfigLse(RCC_LSE_BYPASS,0x1FF);
    #else
            RCC_ConfigLse(RCC_LSE_ENABLE,0x1FF);
    #endif
            lse_ready_count=0;
            /****Waite LSE Ready *****/
            while((RCC_GetFlagStatus(RCC_LDCTRL_FLAG_LSERD) == RESET) && (lse_ready_count<RTC_LSE_TRY_COUNT))
            {
                lse_ready_count++;
                User_Delay_xms(10);
                /****LSE Ready failed or timeout*****/
                if(lse_ready_count>=RTC_LSE_TRY_COUNT)
                {
                   Status = ERROR;
                   log_info("\r\n RTC_ClkSrc Set LSE Faile! \r\n");
                   break;
                }
            }
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSE);
        }
        else
        {
            /* Enable the LSE OSC32_IN PC14 */
            RCC_EnableLsi(DISABLE);
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSE);
    #if (_TEST_LSE_BYPASS_)
            RCC_ConfigLse(RCC_LSE_BYPASS,0x1FF);
    #else
            RCC_ConfigLse(RCC_LSE_ENABLE,0x1FF);
    #endif
          lse_ready_count=0;
          /****Waite LSE Ready *****/
          while((RCC_GetFlagStatus(RCC_LDCTRL_FLAG_LSERD) == RESET) && (lse_ready_count<RTC_LSE_TRY_COUNT))
          {
             lse_ready_count++;
             User_Delay_xms(10);
             /****LSE Ready failed or timeout*****/
             if(lse_ready_count>=RTC_LSE_TRY_COUNT)
             {
                Status = ERROR;
                log_info("\r\n RTC_ClkSrc Set LSE Faile! \r\n");
                break;
             }
          }
        }
        SynchPrediv  = 0xFF; // 32.768KHz
        AsynchPrediv = 0x7F; // value range: 0-7F
    }
    else if (RTC_CLK_SRC_TYPE_LSI == Clk_Src_Type)
    {
        log_info("\r\n RTC_ClkSrc Is Set LSI! \r\n");
        if (true == Is_First_Cfg_RCC)
        {
            /* Enable the LSI OSC */
            RCC_EnableLsi(ENABLE);
            while (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_LSIRD) == RESET)
            {
            }
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);
        }
        else
        {
            RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);
            /* Enable the LSI OSC */
            RCC_EnableLsi(ENABLE);
            while (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_LSIRD) == RESET)
            {
            }
        }
        SynchPrediv  = 0x14A; // 41828Hz
        AsynchPrediv = 0x7F;  // value range: 0-7F
    }
    else
    {
        log_info("\r\n RTC_ClkSrc Value is error! \r\n");
    }
    /* Enable the RTC Clock */
    RCC_EnableRtcClk(ENABLE);
    RTC_WaitForSynchro();
    return Status;
}

/**
 * @brief  RTC alarm config EXTI Interrupt.
 * @param Cmd Interrupt enable or disable
 */
void EXTI18_RTCAlarm_Configuration(FunctionalState Cmd)
{
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;

    EXTI_ClrITPendBit(EXTI_LINE18);
    EXTI_InitStructure.EXTI_Line = EXTI_LINE18;
    #ifdef __TEST_SEVONPEND_WFE_NVIC_DIS__
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
    #else
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    #endif
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = RTCAlarm_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = Cmd;
    NVIC_Init(&NVIC_InitStructure);
}



