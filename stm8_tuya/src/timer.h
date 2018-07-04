#ifndef __TIMER_H
#define __TIMER_H

void TIM1_Config(void);
void TIM1_SetCompare1(uint16_t);
void TIM1_SetCompare2(uint16_t);
void TIM1_SetCompare3(uint16_t);
void TIM1_SetCompare4(uint16_t);
void TIM1_Cmd(FunctionalState);
uint16_t TIM1_GetCounter(void);
void TIM1_SetCounter(uint16_t);
void TIM1_ClearITPendingBit(TIM1_IT_TypeDef);
FlagStatus TIM1_GetFlagStatus(TIM1_FLAG_TypeDef);
void TIM2_ClearITPendingBit(TIM2_IT_TypeDef);
FlagStatus TIM2_GetFlagStatus(TIM2_FLAG_TypeDef);
uint16_t TIM2_GetCounter(void);
void TIM2_SetCounter(uint16_t);

#endif /* __TIMER_H */
