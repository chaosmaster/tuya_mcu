#ifndef __GPIO_H
#define __GPIO_H

#define DEBOUNCE 2
#define MAX_BUTTONS 3

#define LED_PORT GPIOC
#define LED_1 GPIO_PIN_4
#define LED_2 GPIO_PIN_5
#define LED_3 GPIO_PIN_3
#define PWM GPIO_PIN_7

#define BUTTON_PORT GPIOA
#define BUTTON_1 GPIO_PIN_2
#define BUTTON_2 GPIO_PIN_3
#define BUTTON_3 GPIO_PIN_1
#define BUTTONS ( BUTTON_1 | BUTTON_2 | BUTTON_3 )

#define MISC_PORT GPIOD
#define ESP_GPIO0 GPIO_PIN_4
#define ZERO_X GPIO_PIN_2

void GPIO_Config(void);
void GPIO_Write(GPIO_TypeDef*, GPIO_Pin_TypeDef);
void GPIO_WriteHigh(GPIO_TypeDef*, GPIO_Pin_TypeDef);
void GPIO_WriteLow(GPIO_TypeDef*, GPIO_Pin_TypeDef);
void GPIO_WriteReverse(GPIO_TypeDef*, GPIO_Pin_TypeDef);
uint8_t GPIO_ReadInputData(GPIO_TypeDef*);

#endif /* __GPIO_H */
