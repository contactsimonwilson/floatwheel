#include "ws2812.h"

/** HK32F030MF4P6 chip comes with EEPROM, the following is the read and write storage function */
#define HK32F030M_EE_BEGIN (0x0C000000ul)
#define HK32F030M_EE_END (0x0C0001C0ul)
#define HK32F030M_EE_SIZE (448)

/**************************************************************************************************
 * @brief         根据指定的偏移地址将数据写入EEPROM
 * @param         address:   要写入数据的目标地址,是基于EEPROM起始地址的偏移量 0<=address< HK32F030M_EE_SIZE
 * @param         data_in:   要写入的数据 * @return        0 写入失败      1 写入成功
 * @example       EEPROM_WriteByte(2,0x45);  是将数据写入到HK32F030M_EE_BEGIN+5的地址,如果写入成功则返
 **************************************************************************************************/

void EEPROM_WriteByte(uint32_t address, uint8_t data_in)
{
    FLASH_Unlock();
    EEPROM_EraseByte(address + HK32F030M_EE_BEGIN);
    EEPROM_ProgramByte(address + HK32F030M_EE_BEGIN, data_in);
    FLASH_Lock();
}

/***********************************************************************************************
 * @brief Read data from EEPROM according to the specified offset address
 * @param address: The target address to read data is based on the offset of the EEPROM start address 0<=address< HK32F030M_EE_SIZE
 * @param data_ out: Cache variable pointer of the read data
 * @example uint8_t dataR
 * EEPROM_ReadByte(2,&dataR)   is to read the data from the address HK32F030M_EE_BEGIN+5, if the read is successful, return
**********************************************************************************************/
void EEPROM_ReadByte(uint32_t address, uint8_t *data_out)
{
    *data_out = (*((uint8_t *)(address + HK32F030M_EE_BEGIN)));
}
