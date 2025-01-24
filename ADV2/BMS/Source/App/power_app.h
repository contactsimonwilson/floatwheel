#ifndef __POWER_APP_H
#define __POWER_APP_H

#include "mos.h"
#include "flag.h"
#include "pwr.h"
#include "ldo.h"
#include "led.h"
#include "key.h"
#include "Sleep.h"
#include "charger.h"
#include "User_Delay_Config.h"
 
void Power_Task(void);
void Charger_Task(void);
void Power_On_Detection(void);
void Automatic_Shutdown(void);

#endif

