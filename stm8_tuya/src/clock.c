#include "include.h"

/**
 *
  * @brief  Configure system clock to run at 16Mhz
  * @param  None
  * @retval None
  */
void CLK_Config(void)
{
  /*Initialization of the clock */
  /* Clock divider to HSI/1 */
  //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  /* Clear High speed internal clock prescaler */
  CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV);
  
  /* Set High speed internal clock prescaler */
  CLK->CKDIVR |= (uint8_t)CLK_PRESCALER_HSIDIV1;

  //CLK->HSITRIMR = 1;
}
