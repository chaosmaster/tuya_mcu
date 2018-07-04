#include "include.h"

void EEPROM_Config(void)
{

  FLASH->CR1 = FLASH_CR1_RESET_VALUE;
  FLASH->CR2 = FLASH_CR2_RESET_VALUE;
  FLASH->NCR2 = FLASH_NCR2_RESET_VALUE;
  FLASH->IAPSR &= (uint8_t)(~FLASH_IAPSR_DUL);
  FLASH->IAPSR &= (uint8_t)(~FLASH_IAPSR_PUL);
  (void) FLASH->IAPSR; /* Reading of this register causes the clearing of status flags */

  FLASH->CR1 &= (uint8_t)(~FLASH_CR1_IE);  // Disable interrupts
  EEPROM_Unlock();

  EEPROM_Read(0, (uint8_t *)&FlashBuffer, sizeof(FlashBuffer));
}

void EEPROM_Unlock(void)
{
  FLASH->DUKR = FLASH_RASS_KEY2; /* Warning: keys are reversed on data memory !!! */
  FLASH->DUKR = FLASH_RASS_KEY1;
}

void EEPROM_Lock(void)
{
  /* Lock memory */
  FLASH->IAPSR &= FLASH_MEMTYPE_DATA;
}

/**
  * @brief  Programs a memory block
  * @note   This function should be executed from RAM.
  * @param  BlockNum : The block number
  * @param  Buffer : Pointer to buffer containing source data.
  * @retval None.
  */
void EEPROM_Program(uint16_t BlockNum, uint8_t *Buffer, uint8_t len)
{
  uint16_t Count = 0;
  uint32_t startaddress = 0;
  

  startaddress = FLASH_DATA_START_PHYSICAL_ADDRESS;
  
  /* Point to the first block address */
  startaddress = startaddress + ((uint32_t)BlockNum * FLASH_BLOCK_SIZE);

  /* Copy data bytes from RAM to FLASH memory */
  for(Count = 0; Count < len; Count++)
  {
    //EEPROM_ProgramWord(startaddress + Count, ((uint8_t)(Buffer[Count])));
    EEPROM_ProgramByte(startaddress + Count, ((uint8_t)(Buffer[Count])));
  }
}

void EEPROM_Read(uint16_t BlockNum, uint8_t *Buffer, uint8_t len){
  uint16_t Count = 0;
  uint32_t startaddress = 0;
  
  /* Check parameters */
  startaddress = FLASH_DATA_START_PHYSICAL_ADDRESS;
  
  /* Point to the first block address */
  startaddress = startaddress + ((uint32_t)BlockNum * FLASH_BLOCK_SIZE);
  
  /* Copy data bytes from RAM to FLASH memory */
  /*
  for(Count = 0; Count < len; Count+=4)
  {
    EEPROM_ReadWord(startaddress + Count, (uint32_t *)Buffer[Count]);
  }
  */
  for(Count = 0; Count < len; Count++)
  {
    ((uint8_t)(Buffer)[Count]) = EEPROM_ReadByte(startaddress + Count);
  }
}

/**
  * @brief  Reads any byte from flash memory
  * @note   PointerAttr define is declared in the stm8s.h file to select if 
  *         the pointer will be declared as near (2 bytes) or far (3 bytes).
  * @param  Address : Address to read
  * @retval Value of the byte
  */
uint8_t EEPROM_ReadByte(uint32_t Address)
{
  /* Read byte */
  /* SDCC patch: SDCC requires helper routines for >64kB addresses due to lack of far pointers */
  #ifndef _SDCC_BIGMEM_
    return(*(PointerAttr uint8_t *) (MemoryAddressCast)Address); 
  #else
    return(read_byte_address((MemoryAddressCast) Address));
  #endif // _SDCC_BIGMEM_
}

void EEPROM_ProgramByte(uint32_t Address, uint8_t Data)
{
  /* Program byte */
  /* SDCC patch: SDCC requires helper routines for >64kB addresses due to lack of far pointers */
  #ifndef _SDCC_BIGMEM_
    *(PointerAttr uint8_t*) (MemoryAddressCast)Address = Data;
  #else
    write_byte_address((MemoryAddressCast) Address, Data);
  #endif // _SDCC_BIGMEM_
}

void EEPROM_EraseByte(uint32_t Address)
{
  /* Erase byte */
  /* SDCC patch: SDCC requires helper routines for >64kB addresses due to lack of far pointers */
  #ifndef _SDCC_BIGMEM_
    *(PointerAttr uint8_t*) (MemoryAddressCast)Address = FLASH_CLEAR_BYTE;
  #else
    write_byte_address((MemoryAddressCast) Address, FLASH_CLEAR_BYTE);
  #endif // _SDCC_BIGMEM_
}

void EEPROM_Erase(uint16_t BlockNum, uint8_t len)
{
  uint16_t Count = 0;
  uint32_t startaddress = 0;
  
  uint32_t PointerAttr  *pwFlash;
  
  startaddress = FLASH_DATA_START_PHYSICAL_ADDRESS;
  
  /* Point to the first block address */
  pwFlash = (PointerAttr uint32_t *)(MemoryAddressCast)(startaddress + ((uint32_t)BlockNum * FLASH_BLOCK_SIZE));

  /* Copy data bytes from RAM to FLASH memory */
  for(Count = 0; Count < len; Count++)
  {
    EEPROM_EraseByte(startaddress + Count);
  }
}

