#ifndef __EEPROM_H
#define __EEPROM_H

#include "hk32f030m.h"

void EEPROM_WriteByte(uint32_t address, uint8_t data_in);
void EEPROM_ReadByte(uint32_t address, uint8_t *data_out);

#endif
