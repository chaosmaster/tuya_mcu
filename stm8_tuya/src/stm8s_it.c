/**
  ******************************************************************************
  * @file    stm8s_it.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service 
  *          routine.
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_it.h"
#include "mcu_api.h"
#include "include.h"
#include "gpio.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define OFFSET 300
//#define OFFSET 600
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t zero_x = 0;
uint16_t duty_cycle = 0;
uint16_t counter = 0;
//uint32_t cf = 1;
//extern TYPE_BUFFER_S FlashBuffer;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/


/**
  * @brief Auto Wake Up Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(AWU_IRQHandler, 1)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Clock Controller Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(CLK_IRQHandler, 2)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTA Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  LED_PORT->ODR ^= LED_3;
}

/**
  * @brief External Interrupt PORTB Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTC Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief External Interrupt PORTD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
  uint16_t tmp_zero_x = TIM1_GetCounter();
  frequency = TIM2_GetCounter();
  TIM1_SetCounter(0);
  if(!edges){
    TIM2_SetCounter(0);
    overflow = 0;
    frequency = 0;
  }
  else{
    frequency += (overflow * 65536);
    frequency /= edges;
  }
  //frequency = (((overflow * 65536) ) / edges);
  edges++;
  //TIM2_SetCounter(0);
  //overflow = 0;
  TIM1->IER &= (uint8_t)(~(TIM1_IT_CC1 | TIM1_IT_CC2 | TIM1_IT_CC3 | TIM1_IT_CC4));
  if ((GPIO_ReadInputData(GPIOD) & GPIO_PIN_2) != 0) { // Rising edge only
    if(FlashBuffer.brightness <= 244 || !FlashBuffer.power_switch){
      GPIO_WriteLow(GPIOC, GPIO_PIN_7);
    }
    if(storeeprom) {
      //EEPROM_Erase(0, sizeof(FlashBuffer));
      EEPROM_Program(0, (uint8_t *)&FlashBuffer, sizeof(FlashBuffer));
      storeeprom = 0;
    }
    //if(TIM1_GetCounter() >  0x6000 && TIM1_GetCounter() < 0x9000 && TIM1_GetCounter() < (zero_x - 500)) { // Make sure zero_x is at a sane value
    //if(TIM1_GetCounter() >  0x3000 && TIM1_GetCounter() < 0x4800 && TIM1_GetCounter() < (zero_x - 500)) { // Make sure zero_x is at a sane value
    if(tmp_zero_x >  0x4000 && tmp_zero_x < 0x5000) { // && TIM1_GetCounter() < (zero_x - 500)) { // Make sure zero_x is at a sane value
      if(counter < 255){ // Take an average over 255 (valid) measurements
        if(counter){
          zero_x += tmp_zero_x;
          zero_x /= 2;
        }
        else {
          zero_x = tmp_zero_x;
        }
        counter++;
      }
    }
    if(FlashBuffer.brightness <= 244 || !FlashBuffer.power_switch){
      GPIO_WriteLow(GPIOC, GPIO_PIN_7);
    }
    if(FlashBuffer.power_switch && FlashBuffer.brightness > 11){// && FlashBuffer.brightness <= 244){
      duty_cycle = ((zero_x / 2)  * (1 - (float)FlashBuffer.brightness * (1. / 255)));
      //TIM1_TimeBaseInit(8, TIM1_COUNTERMODE_UP, zero_x, 0);
      TIM1_SetCompare1(duty_cycle - OFFSET);
      TIM1_SetCompare2((zero_x / 2) - OFFSET );
      TIM1_SetCompare3(((zero_x / 2) +  duty_cycle - OFFSET));
      TIM1_SetCompare4(zero_x - OFFSET);
      TIM1->IER |= (uint8_t)(TIM1_IT_CC1 | TIM1_IT_CC2 | TIM1_IT_CC3 | TIM1_IT_CC4);
      //TIM1_Cmd(ENABLE);
    }
    //TIM1_Cmd(ENABLE); // Always enable for button-timing etc (may move to a second timer?)
  }
}

/**
  * @brief External Interrupt PORTE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#if defined (STM8S903) || defined (STM8AF622x) 
/**
  * @brief External Interrupt PORTF Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(EXTI_PORTF_IRQHandler, 8)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S903) || (STM8AF622x) */

#if defined (STM8S208) || defined (STM8AF52Ax)
/**
  * @brief CAN RX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(CAN_RX_IRQHandler, 8)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

/**
  * @brief CAN TX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(CAN_TX_IRQHandler, 9)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S208) || (STM8AF52Ax) */

/**
  * @brief SPI Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI_IRQHandler, 10)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @brief Timer1 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  if (TIM1_GetFlagStatus(TIM1_FLAG_UPDATE) == SET){
    //TIM1_Cmd(DISABLE);
    TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
    //TIM1_SetCounter(0);
    /*
    if(FlashBuffer.brightness <= 244) {
      GPIO_WriteLow(GPIOC, GPIO_PIN_7);
    }
    */
  }
}

/**
  * @brief Timer1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  if (TIM1_GetFlagStatus(TIM1_FLAG_CC1) == SET || TIM1_GetFlagStatus(TIM1_FLAG_CC3) == SET){
    if(FlashBuffer.brightness > 11) {
      GPIO_WriteHigh(GPIOC, GPIO_PIN_7);
      /*if(TIM1_GetFlagStatus(TIM1_FLAG_CC1)){
        TIM1_SetCompare1(zero_x + duty_cycle - OFFSET);
      }*/
    }
    TIM1_ClearITPendingBit(TIM1_IT_CC1);
    TIM1_ClearITPendingBit(TIM1_IT_CC3);
  }
  else if (TIM1_GetFlagStatus(TIM1_FLAG_CC2) == SET || TIM1_GetFlagStatus(TIM1_FLAG_CC4) == SET){
    if(FlashBuffer.brightness <= 244) {
      GPIO_WriteLow(GPIOC, GPIO_PIN_7);
      /*if(TIM1_GetFlagStatus(TIM1_FLAG_CC2)){
        TIM1_SetCompare2(zero_x +  (zero_x / 2) - OFFSET);
      }*/
    }
    if (TIM1_GetFlagStatus(TIM1_FLAG_CC4) == SET){ 
      //TIM1_Cmd(DISABLE);
    }
    TIM1_ClearITPendingBit(TIM1_IT_CC2);
    TIM1_ClearITPendingBit(TIM1_IT_CC4);
    /*
    if(FlashBuffer.power_switch && FlashBuffer.brightness > 11) {
      GPIO_WriteHigh(GPIOC, GPIO_PIN_7);
    }
    */
  }
}

#if defined (STM8S903) || defined (STM8AF622x)
/**
  * @brief Timer5 Update/Overflow/Break/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM5_UPD_OVF_BRK_TRG_IRQHandler, 13)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
 
/**
  * @brief Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM5_CAP_COM_IRQHandler, 14)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

#else /* (STM8S208) || (STM8S207) || (STM8S105) || (STM8S103) || (STM8AF62Ax) || (STM8AF52Ax) || (STM8AF626x) */
/**
  * @brief Timer2 Update/Overflow/Break Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  if (TIM2_GetFlagStatus(TIM2_FLAG_UPDATE) == SET ){
    overflow++;
    TIM2_ClearITPendingBit(TIM2_IT_UPDATE);
  }
 }

/**
  * @brief Timer2 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S903) || (STM8AF622x) */

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
    defined(STM8S005) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8AF626x)
/**
  * @brief Timer3 Update/Overflow/Break Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM3_UPD_OVF_BRK_IRQHandler, 15)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }

/**
  * @brief Timer3 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM3_CAP_COM_IRQHandler, 16)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S208) || (STM8S207) || (STM8S105) || (STM8AF62Ax) || (STM8AF52Ax) || (STM8AF626x) */

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S103) || \
    defined(STM8S003) ||  defined (STM8AF62Ax) || defined (STM8AF52Ax) || defined (STM8S903)
/**
  * @brief UART1 TX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART1 RX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
 {
    LED_PORT->ODR ^= BUTTON_3;
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while ((UART1->SR & (uint8_t)UART1_FLAG_RXNE) != (uint8_t)0x00){
      uart_receive_input(UART1->DR);
    }
    while ((UART1->SR & (uint8_t)UART1_FLAG_OR) != (uint8_t)0x00){
    UART1->DR;
    }

 }
#endif /* (STM8S208) || (STM8S207) || (STM8S103) || (STM8S903) || (STM8AF62Ax) || (STM8AF52Ax) */

#if defined(STM8AF622x)
/**
  * @brief UART4 TX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART4_TX_IRQHandler, 17)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART4 RX Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART4_RX_IRQHandler, 18)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /* (STM8AF622x) */

/**
  * @brief I2C Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C_IRQHandler, 19)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#if defined(STM8S105) || defined(STM8S005) ||  defined (STM8AF626x)
/**
  * @brief UART2 TX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART2 RX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /* (STM8S105) || (STM8AF626x) */

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
/**
  * @brief UART3 TX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART3_TX_IRQHandler, 20)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }

/**
  * @brief UART3 RX interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(UART3_RX_IRQHandler, 21)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /* (STM8S208) || (STM8S207) || (STM8AF52Ax) || (STM8AF62Ax) */

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
/**
  * @brief ADC2 interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(ADC2_IRQHandler, 22)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#else /* STM8S105 or STM8S103 or STM8S903 or STM8AF626x or STM8AF622x */
/**
  * @brief ADC1 interrupt routine.
  * @par Parameters:
  * None
  * @retval 
  * None
  */
 INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
 {
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
 }
#endif /* (STM8S208) || (STM8S207) || (STM8AF52Ax) || (STM8AF62Ax) */

#if defined (STM8S903) || defined (STM8AF622x)
/**
  * @brief Timer6 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM6_UPD_OVF_TRG_IRQHandler, 23)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#else /* STM8S208 or STM8S207 or STM8S105 or STM8S103 or STM8AF52Ax or STM8AF62Ax or STM8AF626x */
/**
  * @brief Timer4 Update/Overflow Interrupt routine.
  * @param  None
  * @retval None
  */
 INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
 {
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
 }
#endif /* (STM8S903) || (STM8AF622x)*/

/**
  * @brief Eeprom EEC Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
