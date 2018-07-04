#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#ifdef MAINWORK_GLOBALS
#define MAINWORK_EXT
#else
#define MAINWORK_EXT extern 
#endif

//==============================================================================
#include                <stm8s.h>
#include                <stm8s_it.h>
#include		<stdio.h>
#include		<stdlib.h>
#include		<string.h>

#include                "wifi.h"
#include                "gpio.h"
#include                "clock.h"
#include                "uart.h"
#include                "timer.h"
#include                "exti.h"
#include                "eeprom.h"
#include                "itc.h"


#define 	PARA_ADDR 					0x0400

#define		SUCCESS							1
#define		ERROR								0

#define		ERROR_NO					0x00
#define		ERROR_E1					0x01
#define		ERROR_E2					0x02
#define		ERROR_E3					0x04
#define		ERROR_E4					0x08

typedef struct {
  uint32_t magic_code;
  uint8_t power_switch;
  uint32_t brightness;
  uint32_t frequency;

} TYPE_BUFFER_S;

MAINWORK_EXT TYPE_BUFFER_S FlashBuffer;
MAINWORK_EXT uint8_t error_type;
MAINWORK_EXT bool storeeprom;
MAINWORK_EXT void Delay(uint16_t);
MAINWORK_EXT uint32_t frequency;
//MAINWORK_EXT uint16_t frequency_mean;
MAINWORK_EXT uint16_t overflow;
MAINWORK_EXT uint8_t edges;
#endif
