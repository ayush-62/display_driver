#include "rcc.h"

void rcc_init(void) {
    // 1. Enable HSI & wait for HSI to become ready
    // RCC->CR |= RCC_CR_HSION;
    // while(!(RCC->CR & RCC_CR_HSIRDY));  // wait for HSI to become ready
    RCC->CR |= RCC_CR_HSEON;
    while(!(RCC->CR & RCC_CR_HSERDY));  // wait for HSI to become ready

    //2. set the POWER ENABLE CLOCK & VOLTAGE REGULATOR
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_VOS;

    //3. configure flash prefetch and latency related settings.
    FLASH->ACR = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_2WS;

    //4. configure prescaler values HCLK, PCLK1, PCLK2
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // 4.1 AHB prescaler
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1 Prescaler
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // APB2 Prescaler

    //5. PLL Configuration
    RCC->PLLCFGR |= (PLLM_VAL << RCC_PLLCFGR_PLLM_Pos) | (PLLN_VAL << RCC_PLLCFGR_PLLN_Pos) | (PLLP_VAL << RCC_PLLCFGR_PLLP_Pos);
    // RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_Msk; // clearing clk src bit selects HSI, 0 - HSI, 1 - HSE
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE; // clearing clk src bit selects HSI, 0 - HSI, 1 - HSE

    //6. Enable PLL & wait for it to become ready
    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY));

    //7. Select clock source as pLL and wait to become ready.
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // checks until SWS bits == [10].
}