#include <stdint.h>
#include "stm32f4xx.h"

void ir_sensor_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;     /* Enable GPIOA Clock */
    volatile uint32_t dummy;
    dummy = RCC->AHB1ENR;
    GPIOA->MODER &= ~(3 << (5 * 2));         /* PA5 INPUT MODE */
    GPIOA->PUPDR &= ~(3 << (5 * 2));        /* Optional Pull-up */
    GPIOA->PUPDR |= (1 << (5 * 2));
}

uint8_t ir_sensor_read(void)                /* Read PA5 State */
{
    return(GPIOA->IDR & (1<<5))?1:0;
}