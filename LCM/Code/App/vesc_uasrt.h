#ifndef __VESC_USART_H
#define __VESC_USART_H

#include <string.h>
#include "hk32f030m.h"
#include "crc.h"
#include "usart.h"
#include "datatypes.h"
#include "eeprom.h"


typedef struct {
	float tempFET;
	float tempMotor;
	float avgMotorCurrent;
	float avgInputCurrent;
	float dutyCycleNow;
	long rpm;
	float inpVoltage;
	float ampHours;
	float ampHoursCharged;
	long tachometer;
	long tachometerAbs;
}dataPackage;
	
extern uint8_t VESC_RX_Buff[256];
extern uint8_t VESC_RX_Flag;
extern dataPackage data;

void Get_Vesc_Pack_Data(COMM_PACKET_ID id);  //Get the normal values from the vesc
void Get_Vesc_Adc_Data();					 //Get footsensor config from vesc (store in eeprom?)
void Get_Eeprom_Data(LCM_COMMANDS command); //Get eeprom data and send back over bluetooth - TODO implement + implement in vesc pkg
uint8_t Protocol_Parse(uint8_t * message);	

#endif


