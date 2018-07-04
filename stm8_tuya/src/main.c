#define MAINWORK_GLOBALS

#include <stm8s.h>
#include <stm8s_it.h>

#include "include.h"

#define FREQUENCY_UPDATE 1000000

extern void Delay(uint16_t nCount);

extern TYPE_BUFFER_S FlashBuffer;

extern bool storeeprom = 0;

extern uint32_t frequency = 0;

extern uint16_t overflow = 0;

extern uint8_t edges = 0;

uint16_t button[MAX_BUTTONS][2] = { {BUTTON_1, LED_1}, {BUTTON_2, LED_2}, {BUTTON_3, LED_3} };
uint8_t button_debounce[MAX_BUTTONS] = {0};
uint32_t button_counter[MAX_BUTTONS] = {0};
bool button_state[MAX_BUTTONS] = {0};
bool last_button_state[MAX_BUTTONS] = {0};
uint32_t frequency_counter = 0;
bool input = 0;

void main(void)
{
  uint8_t i = 0;

  GPIO_Config();
  CLK_Config();
  EEPROM_Config();
  UART_Config();
  TIM1_Config();
  EXTI_Config();

  ITC_Config();

  wifi_protocol_init();
  
  enableInterrupts();
  while (1)
  {
    wifi_uart_service();

    for (i = 0; i < MAX_BUTTONS; ++i){
      input = GPIO_ReadInputData(BUTTON_PORT) & button[i][0];
      if(input != last_button_state[i]){
        button_debounce[i] = 0;
      }
      if(++button_debounce[i] >= DEBOUNCE) {
        if(!input){
          button_counter[i] += TIM1_GetCounter();
          if(FlashBuffer.power_switch){
            if(button_counter[i] >= (50000)){ // 100 ms
              if((button[i][0] == BUTTON_1) && FlashBuffer.brightness <= 252) {
                FlashBuffer.brightness+=3;
                LED_PORT->ODR ^= button[i][1];
                brightness_update();
              }
              else if((button[i][0] == BUTTON_3) && FlashBuffer.brightness >= 3) {
                FlashBuffer.brightness-=3;
                LED_PORT->ODR ^= button[i][1];
                brightness_update();
              }
              button_counter[i] = 0;
            }
          }
          else{
            if(button_counter[i] >= (7500000)){ // 15 s
              if((button[i][0] == BUTTON_3)) {
                GPIO_WriteLow(MISC_PORT, ESP_GPIO0);
              }
              button_counter[i] = 0;
            }
          }
        }
        else{
          button_counter[i] = 0;
        }
        
        if(input != button_state[i]){
          button_state[i] = input;
          if(button_state[i]){
            if((button[i][0] == BUTTON_2)){
              FlashBuffer.power_switch=FlashBuffer.power_switch?0:1;
              //dp_download_handle(DPID_SWITCH, FlashBuffer.power_switch, 0);
              switch_update();
              storeeprom = 1;
            }
            //EEPROM_Erase(0, sizeof(FlashBuffer));
            //
            GPIO_WriteLow(LED_PORT, LED_1);
            GPIO_WriteLow(LED_PORT, LED_3);
            GPIO_WriteHigh(MISC_PORT, ESP_GPIO0);
          }
        }
      }
      last_button_state[i] = input;
    }

    if(FlashBuffer.power_switch){
      GPIO_WriteHigh(LED_PORT, LED_2);
    }
    else {
      GPIO_WriteLow(LED_PORT, LED_2);
    }

    //if(FlashBuffer.frequency > 0 && frequency_counter >= FREQUENCY_UPDATE){
    if(frequency_counter >= FREQUENCY_UPDATE){
      //FlashBuffer.frequency = ((20000000 / frequency_mean) * frequency) / 1000;
      //FlashBuffer.frequency = (16000000 / ((overflow * 65536) + frequency)) * (edges);
      //FlashBuffer.frequency = 16000000 / frequency * edges;
      FlashBuffer.frequency = frequency;
      frequency_update();
      frequency_counter = 0;
      frequency = 0;
      overflow = 0;
      edges = 0;
    }

    frequency_counter+=TIM1_GetCounter();

    Delay(0xFF);
  }
}

void Delay(uint16_t nCount)
{
  uint8_t i;
  for(; nCount !=0 ; nCount--) {
    for(i=255;i!=0;i--) {}
  }
}
