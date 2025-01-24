#ifndef __USER_RTC_CONFIG_H__
#define __USER_RTC_CONFIG_H__


#define    RTC_ALARM_TEST_TYPE_IRQ        0x01
#define    RTC_ALARM_TEST_TYPE_OUTPUT     0x02
#define    RTC_ALARM_TEST_TYPE            RTC_ALARM_TEST_TYPE_IRQ

#define    RTC_ALARM_OUT_TYPE_OPEN_DRAIN  0x01
#define    RTC_ALARM_OUT_TYPE_PULL_PUSH   0x02
#define    RTC_ALARM_OUT_TYPE             RTC_ALARM_OUT_TYPE_PULL_PUSH
#define    RTC_LSE_TRY_COUNT              250

typedef enum {
    RTC_CLK_SRC_TYPE_HSE_DIV32=0x01,
    RTC_CLK_SRC_TYPE_LSE=0x02,
    RTC_CLK_SRC_TYPE_LSI=0x03,
}RTC_CLK_SRC_TYPE;

extern ErrorStatus RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE Clk_Src_Type, bool Is_First_Cfg_RCC);
extern ErrorStatus RTC_TimeRegulate(void);
extern ErrorStatus RTC_DateRegulate(void);
extern ErrorStatus RTC_AlarmRegulate(uint32_t RTC_Alarm);
extern void RTC_DateAndTimeDefaultVale(void);
extern  void RTC_PrescalerConfig(void);

extern void RTC_TimeShow(void);
extern void RTC_DateShow(void);
extern void RTC_AlarmShow(uint8_t AlarmX);
extern void EXTI18_RTCAlarm_Configuration(FunctionalState Cmd);
extern void EXTI_PA7_Configuration(void);
extern void EXTI20_RTCWKUP_Configuration(FunctionalState Cmd);
extern void WakeUpClockSelect(uint8_t WKUPClkSrcSel);
extern void RTC_TimeStampShow(void);

#endif/*__USER_RTC_CONFIG_H__*/
