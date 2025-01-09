#include <stm32f401xe.h>
#include "rcc.h"
#include "ssd1306_oled.h"

#define SAMPLING_FREQ (40)


void systick_init(uint32_t freq) {
    uint32_t period = 84000000/freq;
    
    SysTick->CTRL = 0;
    SysTick->LOAD = period - 1;

    NVIC_SetPriority(SysTick_IRQn, 2);
    SysTick->VAL = 0;
    
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

uint32_t result = 0;

void SysTick_Handler(void) {
    ADC1->CR2 |= 0x40000000;                        // start the conversion
    while(!(ADC1->SR & 2));                         // wait for conversion to complete
    result = ADC1->DR;                              // read the conversion result
    // GPIOC->ODR ^= 0x00002000;
    if(result > 2048) {
        GPIOC->ODR = 0x00000000;
    }
    else {
        GPIOC->ODR = 0x00002000;
    }
    // __asm__("nop");
    // __asm__("nop");
    // __asm__("nop");
}

void gpio_init(void) {
    // set up pin PC13 for led
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;                // 1. Enable GPIOC clock
    GPIOC->MODER |= ( 1 << GPIO_MODER_MODE13_Pos);      // 2. Set mode as output, PA13 - Bits[27:26] = [01] -> output

    // set up pin PA1 for analog input
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;                // 1. Enable GPIOC clock
    GPIOA->MODER |= 0xC;                                // 2. PA1 analog
}

void adc_init(void) {
    // setup ADC1
    RCC->APB2ENR |= 0x00000100;                         // enable ADC clock
    ADC1->SMPR2 = 0;                                    // sampling time 3 cycles for channel 1
    ADC1->CR1 |= 1;                                     //  Analog input channel 1
    ADC1->CR2 = 0;                                      // software trigger
    ADC1->SQR3 = 1;                                     // Conversion sequence starts at channel 1
    ADC1->SQR1 = 0;                                     // Sequence Length = 1
    ADC1->CR2 |= 1;                                     // Enable ADC1
}



int main(void) {
    rcc_init();
    gpio_init();
    // adc_init();
    // systick_init(SAMPLING_FREQ);

    GPIOC->ODR = 0x00000000;

    // for(int i = 0; i < 10000000; i++) {
    //     __asm__("nop");
    // }
    OLED_init();
    OLED_Clear();

    drawLine();

    display();
    while(1) {
        // ADC1->CR2 |= 0x40000000;                        // start the conversion
        // while(!(ADC1->SR & 2));                         // wait for conversion to complete
        // result = ADC1->DR;                              // read the conversion result
        GPIOC->ODR ^= 0x00002000;
        for(int i = 0; i < 10000000; i++) {
            __asm__("nop");
        }
        // if(result > 2048) {
        //     GPIOC->ODR = 0x00000000;
        // }
        // else {
        //     GPIOC->ODR = 0x00002000;
        // }
    }

    return 0;
}
