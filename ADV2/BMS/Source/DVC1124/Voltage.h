#ifndef VOLTAGE_H__
#define VOLTAGE_H__
#include "DVC11XX.h"
//------------------------------------------------------------------------------
float DVC11XX_Calc_VCell(u8 cellIndex);
u32 DVC11XX_Calc_VBAT(void);
u32 DVC11XX_Calc_VLOAD(void);
u32 DVC11XX_Calc_VPACK(void);
u16 DVC11XX_Calc_V1P8(void);
void CellTestClose(u32 cellnumber);
//------------------------------------------------------------------------------
#endif
