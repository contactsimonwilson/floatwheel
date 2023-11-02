#ifndef __FLAG_BIT_H
#define __FLAG_BIT_H

#include "hk32f030m.h"

extern uint8_t Power_Flag;
extern uint8_t Charge_Flag;
extern uint8_t WS2812_Display_Flag;
extern uint8_t WS2812_Flag;
extern uint8_t Power_Display_Flag;
extern uint8_t Buzzer_Flag;
extern uint8_t Usart_Flag;

extern uint16_t Buzzer_Time;
extern uint16_t Charge_Time;
extern uint16_t Flashlight_Time;
extern uint16_t Power_Time;
extern uint16_t Usart_Time;
extern uint16_t ADC_Time;
extern uint16_t Shutdown_Time_S;
extern uint8_t Shutdown_Time_M;

extern float ADC1_Val;
extern float ADC2_Val;
extern float Charge_Voltage;
extern uint8_t Gear_Position;
extern uint8_t WS2812_Measure;
extern uint8_t Buzzer_Frequency;
extern uint16_t Flashlight_Detection_Time;
extern float Charge_Current;
extern uint8_t V_I;
extern uint8_t Shutdown_Cnt;
extern uint16_t Charger_Detection_1ms;

#endif


