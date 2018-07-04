#ifndef __EEPROM_H
#define __EEPROM_H

void EEPROM_Config(void);
void EEPROM_Unlock(void);
void EEPROM_Lock(void);
void EEPROM_Erase(uint16_t, uint8_t);
void EEPROM_Program(uint16_t, uint8_t *, uint8_t);
uint8_t EEPROM_ReadByte(uint32_t);
void EEPROM_Read(uint16_t, uint8_t *, uint8_t);
void EEPROM_ProgramByte(uint32_t, uint8_t);
void EEPROM_EraseByte(uint32_t);

#define OPERATION_TIMEOUT   ((uint16_t)0xFFFF)
#define FLASH_CLEAR_BYTE    ((uint8_t)0x00)

#endif /* __EEPROM_H */
