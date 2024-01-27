#ifndef __ADC_H
#define __ADC_H

#include "hk32f030m.h"


void ADC1_Init(void);
uint16_t Read_ADC_Value(uint8_t ch);

#endif


