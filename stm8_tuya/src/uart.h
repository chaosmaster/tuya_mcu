/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __UART_H
#define __UART_H

/* Includes ------------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifdef _RAISONANCE_
#define PUTCHAR_PROTOTYPE int uart_putchar (char c)
#define GETCHAR_PROTOTYPE int uart_getchar (void)
#elif defined (_COSMIC_)
#define PUTCHAR_PROTOTYPE char uart_putchar (char c)
#define GETCHAR_PROTOTYPE char uart_getchar (void)
#elif defined (_SDCC_)                    /* SDCC patch: same types as stdio.h */
 #if SDCC_VERSION >= 30605                /* putchar() was changed for >=3.6.5, see sdcc manual */
  #define PUTCHAR_PROTOTYPE int uart_putchar (int c)
 #else
  #define PUTCHAR_PROTOTYPE void uart_putchar (char c)
 #endif 
 #define GETCHAR_PROTOTYPE char uart_getchar (void)
#else /* _IAR_ */
#define PUTCHAR_PROTOTYPE int uart_putchar (int c)
#define GETCHAR_PROTOTYPE int uart_getchar (void)
#endif /* _RAISONANCE_ */
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Exported functions ------------------------------------------------------- */
PUTCHAR_PROTOTYPE;
GETCHAR_PROTOTYPE;

void UART_Config(void);
#endif /* __UART_H */
