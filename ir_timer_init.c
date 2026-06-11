#include <stdint.h>
#include "stm32f4xx.h"

void ir_timer_init(void)
{
    RCC->APB1ENR |=RCC_APB1ENR_TIM2EN;

    volatile uint32_t dummy;

    dummy =RCC->APB1ENR;
    TIM2->PSC = 15;
    TIM2->ARR = 0xFFFFFFFF;
    TIM2->CNT = 0;
    TIM2->CR1 |=TIM_CR1_CEN;
}