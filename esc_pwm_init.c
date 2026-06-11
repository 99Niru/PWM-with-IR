#include <stdint.h>
#include "stm32f4xx.h"

void esc_pwm_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    volatile uint32_t dummy;

    dummy = RCC->AHB1ENR;
    dummy = RCC->APB1ENR;

    GPIOB->MODER &= ~(3 << (6 * 2));
    GPIOB->MODER |= (2 << (6 * 2));
    GPIOB->AFR[0] &= ~(0xF << (6 * 4));
    GPIOB->AFR[0] |= (2 << (6 * 4));

    TIM4->PSC = 15;
    TIM4->ARR = 19999;
    TIM4->CCR1 = 1000;
    TIM4->CCMR1 &= ~(7 << 4);
    TIM4->CCMR1 |= (6 << 4);
    TIM4->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM4->CCER |= TIM_CCER_CC1E;
    TIM4->CR1 |= TIM_CR1_ARPE;
    TIM4->EGR |= TIM_EGR_UG;
    TIM4->CR1 |= TIM_CR1_CEN;
}