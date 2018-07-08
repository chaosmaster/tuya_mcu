#include "include.h"

void TIM1_Config(void)
{
  //TIM1_DeInit();
  TIM1->CR1  = TIM1_CR1_RESET_VALUE;
  TIM1->CR2  = TIM1_CR2_RESET_VALUE;
  TIM1->SMCR = TIM1_SMCR_RESET_VALUE;
  TIM1->ETR  = TIM1_ETR_RESET_VALUE;
  TIM1->IER  = TIM1_IER_RESET_VALUE;
  TIM1->SR2  = TIM1_SR2_RESET_VALUE;
  /* Disable channels */
  TIM1->CCER1 = TIM1_CCER1_RESET_VALUE;
  TIM1->CCER2 = TIM1_CCER2_RESET_VALUE;
  /* Configure channels as inputs: it is necessary if lock level is equal to 2 or 3 */
  TIM1->CCMR1 = 0x01;
  TIM1->CCMR2 = 0x01;
  TIM1->CCMR3 = 0x01;
  TIM1->CCMR4 = 0x01;
  /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
  TIM1->CCER1 = TIM1_CCER1_RESET_VALUE;
  TIM1->CCER2 = TIM1_CCER2_RESET_VALUE;
  TIM1->CCMR1 = TIM1_CCMR1_RESET_VALUE;
  TIM1->CCMR2 = TIM1_CCMR2_RESET_VALUE;
  TIM1->CCMR3 = TIM1_CCMR3_RESET_VALUE;
  TIM1->CCMR4 = TIM1_CCMR4_RESET_VALUE;
  TIM1->CNTRH = TIM1_CNTRH_RESET_VALUE;
  TIM1->CNTRL = TIM1_CNTRL_RESET_VALUE;
  TIM1->PSCRH = TIM1_PSCRH_RESET_VALUE;
  TIM1->PSCRL = TIM1_PSCRL_RESET_VALUE;
  TIM1->ARRH  = TIM1_ARRH_RESET_VALUE;
  TIM1->ARRL  = TIM1_ARRL_RESET_VALUE;
  TIM1->CCR1H = TIM1_CCR1H_RESET_VALUE;
  TIM1->CCR1L = TIM1_CCR1L_RESET_VALUE;
  TIM1->CCR2H = TIM1_CCR2H_RESET_VALUE;
  TIM1->CCR2L = TIM1_CCR2L_RESET_VALUE;
  TIM1->CCR3H = TIM1_CCR3H_RESET_VALUE;
  TIM1->CCR3L = TIM1_CCR3L_RESET_VALUE;
  TIM1->CCR4H = TIM1_CCR4H_RESET_VALUE;
  TIM1->CCR4L = TIM1_CCR4L_RESET_VALUE;
  TIM1->OISR  = TIM1_OISR_RESET_VALUE;
  TIM1->EGR   = 0x01; /* TIM1_EGR_UG */
  TIM1->DTR   = TIM1_DTR_RESET_VALUE;
  TIM1->BKR   = TIM1_BKR_RESET_VALUE;
  TIM1->RCR   = TIM1_RCR_RESET_VALUE;
  TIM1->SR1   = TIM1_SR1_RESET_VALUE;

  //TIM1_TimeBaseInit(16, TIM1_COUNTERMODE_UP, 0xFFFF, 0);
  //
  /* Set the Autoreload value */
  TIM1->ARRH = (uint8_t)(0xFF);
  TIM1->ARRL = (uint8_t)(0xFF);

  /* Set the Prescaler value */
  TIM1->PSCRH = (uint8_t)(0x00);
  TIM1->PSCRL = (uint8_t)(0x10 - 1);  // 16 (used value is register + 1)
  // prescaler on 16 gives 1 tick per us

  /* Select the Counter Mode */
  TIM1->CR1 = (uint8_t)((uint8_t)(TIM1->CR1 & (uint8_t)(~(TIM1_CR1_CMS | TIM1_CR1_DIR)))
                        | (uint8_t)(TIM1_COUNTERMODE_UP));
  
  //TIM1_ITConfig(TIM1_IT_CC1 | TIM1_IT_CC2 | TIM1_IT_CC3 | TIM1_IT_CC4, ENABLE);
  TIM1->IER |= (uint8_t)(TIM1_IT_CC1 | TIM1_IT_CC2 | TIM1_IT_CC3 | TIM1_IT_CC4);

  /* TIM1 counter enable */
  TIM1_Cmd(ENABLE);

  TIM2->CR1 = (uint8_t)TIM2_CR1_RESET_VALUE;
  TIM2->IER = (uint8_t)TIM2_IER_RESET_VALUE;
  TIM2->SR2 = (uint8_t)TIM2_SR2_RESET_VALUE;
  
  /* Disable channels */
  TIM2->CCER1 = (uint8_t)TIM2_CCER1_RESET_VALUE;
  TIM2->CCER2 = (uint8_t)TIM2_CCER2_RESET_VALUE;
  
  
  /* Then reset channel registers: it also works if lock level is equal to 2 or 3 */
  TIM2->CCER1 = (uint8_t)TIM2_CCER1_RESET_VALUE;
  TIM2->CCER2 = (uint8_t)TIM2_CCER2_RESET_VALUE;
  TIM2->CCMR1 = (uint8_t)TIM2_CCMR1_RESET_VALUE;
  TIM2->CCMR2 = (uint8_t)TIM2_CCMR2_RESET_VALUE;
  TIM2->CCMR3 = (uint8_t)TIM2_CCMR3_RESET_VALUE;
  TIM2->CNTRH = (uint8_t)TIM2_CNTRH_RESET_VALUE;
  TIM2->CNTRL = (uint8_t)TIM2_CNTRL_RESET_VALUE;
  TIM2->PSCR = (uint8_t)TIM2_PSCR_RESET_VALUE;
  TIM2->ARRH  = (uint8_t)TIM2_ARRH_RESET_VALUE;
  TIM2->ARRL  = (uint8_t)TIM2_ARRL_RESET_VALUE;
  TIM2->CCR1H = (uint8_t)TIM2_CCR1H_RESET_VALUE;
  TIM2->CCR1L = (uint8_t)TIM2_CCR1L_RESET_VALUE;
  TIM2->CCR2H = (uint8_t)TIM2_CCR2H_RESET_VALUE;
  TIM2->CCR2L = (uint8_t)TIM2_CCR2L_RESET_VALUE;
  TIM2->CCR3H = (uint8_t)TIM2_CCR3H_RESET_VALUE;
  TIM2->CCR3L = (uint8_t)TIM2_CCR3L_RESET_VALUE;
  TIM2->SR1 = (uint8_t)TIM2_SR1_RESET_VALUE;

  /* Set the Prescaler value */
  TIM2->PSCR = (uint8_t)(TIM2_PRESCALER_1);
  /* Set the Autoreload value */
  TIM2->ARRH = (uint8_t)(0xFF);
  TIM2->ARRL = (uint8_t)(0xFF);
  TIM2->IER |= (uint8_t)TIM2_IT_UPDATE;

  TIM2->CR1 |= (uint8_t)TIM2_CR1_CEN;
}

/**
  * @brief  Sets the TIM1 Capture Compare1 Register value.
  * @param   Compare1 specifies the Capture Compare1 register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM1_SetCompare1(uint16_t Compare1)
{
  /* Set the Capture Compare1 Register value */
  TIM1->CCR1H = (uint8_t)(Compare1 >> 8);
  TIM1->CCR1L = (uint8_t)(Compare1);
}

/**
  * @brief  Sets the TIM1 Capture Compare2 Register value.
  * @param   Compare2 specifies the Capture Compare2 register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM1_SetCompare2(uint16_t Compare2)
{
  /* Set the Capture Compare2 Register value */
  TIM1->CCR2H = (uint8_t)(Compare2 >> 8);
  TIM1->CCR2L = (uint8_t)(Compare2);
}

/**
  * @brief  Sets the TIM1 Capture Compare3 Register value.
  * @param   Compare3 specifies the Capture Compare3 register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM1_SetCompare3(uint16_t Compare3)
{
  /* Set the Capture Compare3 Register value */
  TIM1->CCR3H = (uint8_t)(Compare3 >> 8);
  TIM1->CCR3L = (uint8_t)(Compare3);
}

/**
  * @brief  Sets the TIM1 Capture Compare4 Register value.
  * @param   Compare4 specifies the Capture Compare4 register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM1_SetCompare4(uint16_t Compare4)
{
  /* Set the Capture Compare4 Register value */
  TIM1->CCR4H = (uint8_t)(Compare4 >> 8);
  TIM1->CCR4L = (uint8_t)(Compare4);
}

void TIM1_Cmd(FunctionalState NewState)
{
  /* set or Reset the CEN Bit */
  if (NewState != DISABLE)
  {
    TIM1->CR1 |= TIM1_CR1_CEN;
  }
  else
  {
    TIM1->CR1 &= (uint8_t)(~TIM1_CR1_CEN);
  }
}


uint16_t TIM1_GetCounter(void)
{
  uint16_t tmpcntr = 0;
  
  tmpcntr = ((uint16_t)TIM1->CNTRH << 8);
  
  /* Get the Counter Register value */
  return (uint16_t)(tmpcntr | (uint16_t)(TIM1->CNTRL));
}

/**
  * @brief  Sets the TIM1 Counter Register value.
  * @param   Counter specifies the Counter register new value.
  * This parameter is between 0x0000 and 0xFFFF.
  * @retval None
  */
void TIM1_SetCounter(uint16_t Counter)
{
  /* Set the Counter Register value */
  TIM1->CNTRH = (uint8_t)(Counter >> 8);
  TIM1->CNTRL = (uint8_t)(Counter);
}

void TIM1_ClearITPendingBit(TIM1_IT_TypeDef TIM1_IT)
{
  /* Clear the IT pending Bit */
  TIM1->SR1 = (uint8_t)(~(uint8_t)TIM1_IT);
}

FlagStatus TIM1_GetFlagStatus(TIM1_FLAG_TypeDef TIM1_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint8_t tim1_flag_l = 0, tim1_flag_h = 0;
  
  tim1_flag_l = (uint8_t)(TIM1->SR1 & (uint8_t)TIM1_FLAG);
  tim1_flag_h = (uint8_t)((uint16_t)TIM1_FLAG >> 8);
  
  if ((tim1_flag_l | (uint8_t)(TIM1->SR2 & tim1_flag_h)) != 0)
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return (FlagStatus)(bitstatus);
}

void TIM2_ClearITPendingBit(TIM2_IT_TypeDef TIM2_IT)
{
  /* Clear the IT pending Bit */
  TIM2->SR1 = (uint8_t)(~TIM2_IT);
}

FlagStatus TIM2_GetFlagStatus(TIM2_FLAG_TypeDef TIM2_FLAG)
{
  FlagStatus bitstatus = RESET;
  uint8_t tim2_flag_l = 0, tim2_flag_h = 0;
  
  tim2_flag_l = (uint8_t)(TIM2->SR1 & (uint8_t)TIM2_FLAG);
  tim2_flag_h = (uint8_t)((uint16_t)TIM2_FLAG >> 8);
  
  if ((tim2_flag_l | (uint8_t)(TIM2->SR2 & tim2_flag_h)) != (uint8_t)RESET )
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  return (FlagStatus)bitstatus;
}

uint16_t TIM2_GetCounter(void)
{
  /* Get the Counter Register value */
  return (uint16_t)( ((uint16_t)TIM2->CNTRH << 8)| (uint16_t)(TIM2->CNTRL));
}

void TIM2_SetCounter(uint16_t Counter)
{
  /* Set the Counter Register value */
  TIM2->CNTRH = (uint8_t)(Counter >> 8);
  TIM2->CNTRL = (uint8_t)(Counter);
}
