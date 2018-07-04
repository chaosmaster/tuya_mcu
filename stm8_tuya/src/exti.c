#include "include.h"

void EXTI_Config(void)
{

  /* Initialize the Interrupt sensitivity */
  //EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_FALL);
  //EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_ONLY);
  // PORTA
  EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PAIS);
  EXTI->CR1 |= (uint8_t)(EXTI_SENSITIVITY_RISE_FALL);
  // PORTD
  EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PDIS);
  EXTI->CR1 |= (uint8_t)((uint8_t)(EXTI_SENSITIVITY_RISE_ONLY) << 6);

  
}
