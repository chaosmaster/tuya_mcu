#include "include.h"

void UART_Config(void)
{
  /* Clear the Idle Line Detected bit in the status register by a read
  to the UART1_SR register followed by a Read to the UART1_DR register */
  (void)UART1->SR;
  (void)UART1->DR;

  UART1->BRR2 = UART1_BRR2_RESET_VALUE;  /* Set UART1_BRR2 to reset value 0x00 */
  UART1->BRR1 = UART1_BRR1_RESET_VALUE;  /* Set UART1_BRR1 to reset value 0x00 */

  UART1->CR1 = UART1_CR1_RESET_VALUE;  /* Set UART1_CR1 to reset value 0x00 */
  UART1->CR2 = UART1_CR2_RESET_VALUE;  /* Set UART1_CR2 to reset value 0x00 */
  UART1->CR3 = UART1_CR3_RESET_VALUE;  /* Set UART1_CR3 to reset value 0x00 */
  UART1->CR4 = UART1_CR4_RESET_VALUE;  /* Set UART1_CR4 to reset value 0x00 */
  UART1->CR5 = UART1_CR5_RESET_VALUE;  /* Set UART1_CR5 to reset value 0x00 */

  UART1->GTR = UART1_GTR_RESET_VALUE;
  UART1->PSCR = UART1_PSCR_RESET_VALUE;

  /* Set the word length bit according to UART1_WordLength value */
  UART1->CR1 |= (uint8_t)UART1_WORDLENGTH_8D;
  
  /* Set the STOP bits number according to UART1_StopBits value  */
  UART1->CR3 |= (uint8_t)UART1_STOPBITS_1;  
  
  /* Set the Parity Control bit to UART1_Parity value */
  UART1->CR1 |= (uint8_t)UART1_PARITY_NO;  
  
  UART1->BRR2 = 0x02;
  UART1->BRR1 = 0x68;
  
  /* Set the Clock Polarity, lock Phase, Last Bit Clock pulse */
  UART1->CR3 &= (uint8_t)((uint8_t)UART1_SYNCMODE_CLOCK_DISABLE & (uint8_t)(UART1_CR3_CPOL | 
                                                        UART1_CR3_CPHA | UART1_CR3_LBCL));  
  /* Set the Transmitter Enable bit */
  UART1->CR2 |= (uint8_t)UART1_CR2_TEN;  
  /* Set the Receiver Enable bit */
  UART1->CR2 |= (uint8_t)UART1_CR2_REN;  

  /* Clear the Clock Enable bit */
  UART1->CR3 &= (uint8_t)(~UART1_CR3_CKEN); 
  
  //UART1_ITConfig(UART1_IT_TXE, ENABLE);
  UART1->CR2 |= (uint8_t)((uint8_t)1 << (uint8_t)((uint8_t)UART1_IT_RXNE_OR & (uint8_t)0x0F));

}

/**
  * @brief Retargets the C library printf function to the UART.
  * @param c Character to send
  * @retval char Character sent
  */
PUTCHAR_PROTOTYPE
{
  while ((UART1->SR & (uint8_t)UART1_FLAG_TXE) == (uint8_t)0x00);
  /* Write a character to the UART1 */
  UART1->DR = c;
  /* Loop until the end of transmission */
  while ((UART1->SR & (uint8_t)UART1_FLAG_TXE) == (uint8_t)0x00);
  
//#if !defined (_SDCC_) || (SDCC_VERSION >= 30605)    /* uart_putchar() was changed for >=3.6.5, see sdcc manual */
//    return (c);
//#endif
}

/**
  * @brief Retargets the C library scanf function to the USART.
  * @param None
  * @retval char Character to Read
  */
GETCHAR_PROTOTYPE
{
  return ((uint8_t)UART1->DR);
}
