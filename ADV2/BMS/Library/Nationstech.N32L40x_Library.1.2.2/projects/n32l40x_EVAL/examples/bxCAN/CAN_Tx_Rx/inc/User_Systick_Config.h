#ifndef  __USER_SYSTICK_CONFIG_H__
#define  __USER_SYSTICK_CONFIG_H__

#define  TIME_1MS      1
#define  TIME_10MS    (TIME_1MS*10)
#define  TIME_100MS   (TIME_10MS*10)
#define  TIME_1S      (TIME_100MS*10)

extern uint32_t systick_count;
extern void Systick_MS_Config(uint32_t sys_freq);
extern void Systick_Disable(void);
extern uint32_t User_Time_Read(uint32_t time);
extern void User_Time_Set(uint32_t* time);


#endif/**/
