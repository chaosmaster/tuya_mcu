#include "include.h"

void ITC_Config(void)
{

  ITC_SetSoftwarePriority(ITC_IRQ_UART1_RX, ITC_PRIORITYLEVEL_0);
  
}

/**
  * @brief  Sets the software priority of the specified interrupt source.
  * @note   - The modification of the software priority is only possible when
  *         the interrupts are disabled.
  *         - The normal behavior is to disable the interrupt before calling
  *         this function, and re-enable it after.
  *         - The priority level 0 cannot be set (see product specification
  *         for more details).
  * @param  IrqNum : Specifies the peripheral interrupt source.
  * @param  PriorityValue : Specifies the software priority value to set,
  *         can be a value of @ref  ITC_PriorityLevel_TypeDef .
  * @retval None
*/
void ITC_SetSoftwarePriority(ITC_Irq_TypeDef IrqNum, ITC_PriorityLevel_TypeDef PriorityValue)
{
  uint8_t Mask = 0;
  uint8_t NewPriority = 0;
  
  /* Define the mask corresponding to the bits position in the SPR register */
  /* The mask is reversed in order to clear the 2 bits after more easily */
  Mask = (uint8_t)(~(uint8_t)(0x03U << (((uint8_t)IrqNum % 4U) * 2U)));
  
  /* Define the new priority to write */
  NewPriority = (uint8_t)((uint8_t)(PriorityValue) << (((uint8_t)IrqNum % 4U) * 2U));
  
  switch (IrqNum)
  {
  case ITC_IRQ_TLI: /* TLI software priority can be written but has no meaning */
  case ITC_IRQ_AWU:
  case ITC_IRQ_CLK:
  case ITC_IRQ_PORTA:
    ITC->ISPR1 &= Mask;
    ITC->ISPR1 |= NewPriority;
    break;
    
  case ITC_IRQ_PORTB:
  case ITC_IRQ_PORTC:
  case ITC_IRQ_PORTD:
  case ITC_IRQ_PORTE:
    ITC->ISPR2 &= Mask;
    ITC->ISPR2 |= NewPriority;
    break;
    
#if defined(STM8S208) || defined(STM8AF52Ax)
  case ITC_IRQ_CAN_RX:
  case ITC_IRQ_CAN_TX:
#endif /*STM8S208 or STM8AF52Ax */
#if defined(STM8S903) || defined(STM8AF622x)
  case ITC_IRQ_PORTF:
#endif /*STM8S903 or STM8AF622x */
  case ITC_IRQ_SPI:
  case ITC_IRQ_TIM1_OVF:
    ITC->ISPR3 &= Mask;
    ITC->ISPR3 |= NewPriority;
    break;
    
  case ITC_IRQ_TIM1_CAPCOM:
#if defined(STM8S903) || defined(STM8AF622x) 
  case ITC_IRQ_TIM5_OVFTRI:
  case ITC_IRQ_TIM5_CAPCOM:
#else
  case ITC_IRQ_TIM2_OVF:
  case ITC_IRQ_TIM2_CAPCOM:
#endif /*STM8S903 or STM8AF622x */
  case ITC_IRQ_TIM3_OVF:
    ITC->ISPR4 &= Mask;
    ITC->ISPR4 |= NewPriority;
    break;
    
  case ITC_IRQ_TIM3_CAPCOM:
#if defined(STM8S208) ||defined(STM8S207) || defined (STM8S007) || defined(STM8S103) || \
    defined(STM8S003) ||defined(STM8S903) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
  case ITC_IRQ_UART1_TX:
  case ITC_IRQ_UART1_RX:
#endif /*STM8S208 or STM8S207 or STM8S007 or STM8S103 or STM8S003 or STM8S903 or STM8AF52Ax or STM8AF62Ax */ 
#if defined(STM8AF622x)
  case ITC_IRQ_UART4_TX:
  case ITC_IRQ_UART4_RX:
#endif /*STM8AF622x */
  case ITC_IRQ_I2C:
    ITC->ISPR5 &= Mask;
    ITC->ISPR5 |= NewPriority;
    break;
    
#if defined(STM8S105) || defined(STM8S005) || defined(STM8AF626x)
  case ITC_IRQ_UART2_TX:
  case ITC_IRQ_UART2_RX:
#endif /*STM8S105 or STM8AF626x */
    
#if defined(STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8AF52Ax) || \
    defined(STM8AF62Ax)
  case ITC_IRQ_UART3_TX:
  case ITC_IRQ_UART3_RX:
  case ITC_IRQ_ADC2:
#endif /*STM8S208 or STM8S207 or STM8AF52Ax or STM8AF62Ax */
    
#if defined(STM8S105) || defined(STM8S005) || defined(STM8S103) || defined(STM8S003) || \
    defined(STM8S903) || defined(STM8AF626x) || defined (STM8AF622x)
  case ITC_IRQ_ADC1:
#endif /*STM8S105, STM8S005, STM8S103 or STM8S003 or STM8S903 or STM8AF626x or STM8AF622x */
    
#if defined (STM8S903) || defined (STM8AF622x)
  case ITC_IRQ_TIM6_OVFTRI:
#else
  case ITC_IRQ_TIM4_OVF:
#endif /* STM8S903 or STM8AF622x */
    ITC->ISPR6 &= Mask;
    ITC->ISPR6 |= NewPriority;
    break;
    
  case ITC_IRQ_EEPROM_EEC:
    ITC->ISPR7 &= Mask;
    ITC->ISPR7 |= NewPriority;
    break;
    
  default:
    break;
  }
}
