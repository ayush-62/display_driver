#ifndef _RCC_H_
#define _RCC_H_

#include <stm32f401xe.h>

#define PLLM_VAL 25
#define PLLN_VAL 336
#define PLLP_VAL 0b01   // PLLP devide values [0b00 - /2, 0b01 - /4, 0b10 - /6, 0b11 - /8]  
#define PLLQ_VAL 7
#define PLLR_VAL 0


void rcc_init(void);

#endif