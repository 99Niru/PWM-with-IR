#include <stdint.h>
#include <stdio.h>

#include "stm32f4xx.h"

void usart_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    volatile uint32_t dummy;
    dummy = RCC->AHB1ENR;

    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    dummy = RCC->APB1ENR;

    GPIOB->MODER &= ~((3<<(10*2)) | (3<<(11*2)));
    GPIOB->MODER |=(2<<(10*2)) | (2<<(11*2));

    GPIOB->AFR[1] &= ~((0xF<<8) |(0xF<<12));
    GPIOB->AFR[1] |= (7<<8) | (7<<12);

    USART3->BRR = 139; 
    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_RE;
    USART3->CR1 |= USART_CR1_UE;   
}

int _write(int file,char *ptr,int len)
{
    for(int i=0;i<len;i++)
    {
        while(!(USART3->SR & USART_SR_TXE));
        USART3->DR = ptr[i];
    }
    return len;
}

void usart_write(USART_TypeDef *usart, char c)
{
    while(!(usart->SR & USART_SR_TXE));
    usart->DR = c;
}

void usart_write_string( USART_TypeDef *usart, const char *str)
    {
        while(*str)
        {
        usart_write(usart,*str);
        str++;
        }
    }

char usart_read(USART_TypeDef *usart)
{
    while(!(usart->SR & USART_SR_RXNE));

       return (char)(usart->DR & 0xFF) ;
} 
 