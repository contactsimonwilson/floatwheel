#ifndef __USER_RTC_CONFIG_H__
#define __USER_RTC_CONFIG_H__

typedef enum {
    RTC_CLK_SRC_TYPE_HSE_DIV32=0x01,
    RTC_CLK_SRC_TYPE_LSE=0x02,
    RTC_CLK_SRC_TYPE_LSI=0x03,
}RTC_CLK_SRC_TYPE;

extern void RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE Clk_Src_Type, bool Is_First_Cfg_RCC, bool Is_Rst_Bkp);
extern ErrorStatus RTC_TimeRegulate(void);
extern ErrorStatus RTC_DateRegulate(void);
extern ErrorStatus RTC_AlarmRegulate(uint32_t RTC_Alarm);
extern void RTC_DateAndTimeDefaultVale(void);
extern void RTC_PrescalerConfig(void);
extern void EXTI_PA11_Configuration(void);
extern void RTC_TimeShow(void);
extern void RTC_DateShow(void);
extern void RTC_AlarmShow(uint8_t AlarmX);
extern void EXTI18_RTCAlarm_Configuration(FunctionalState Cmd);

#endif/*__USER_RTC_CONFIG_H__*/
