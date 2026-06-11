/* #include <stdint.h>
#include "stm32f4xx.h"
#include <stdio.h>

void esc_pwm_init(void);
void usart_init(void);
void usart_write(USART_TypeDef *usart, char c);
void usart_write_string( USART_TypeDef *usart, const char *str);
volatile uint32_t ticks = 0;
void delay_ms(uint32_t ms);
char usart_read(USART_TypeDef *usart);


int main(void)
{
    char ch=0;
    volatile uint32_t duty=0;
    esc_pwm_init();
    usart_init();
    SysTick_Config(16000); // volatile uint32_t ticks = 0;
    //TIM4->CCR1 = 1000;
    //printf("----------Welcome----------\r\n");
    //usart_write(USART3,'A');
    //usart_write_string( USART3, "\n Hello World\r\n");
    delay_ms(5000);

    while(1)
    {   /* 
        usart_write_string( USART3, "\n ----- Select the Option ----- \r\n 0-> OFF \r\n 1-> LOW SPEED \r\n 2-> MEDIUM SPEED \r\n 3-> HIGH SPEED \n");
        ch = usart_read(USART3);
        
        if(ch=='1')
        {
        TIM4->CCR1 = 1300;
        printf("\x1B[2J\x1B[H LOW SPEED CCR=%lu Duty=%.2f%%\r\n",TIM4->CCR1,(TIM4->CCR1*100.0f)/(19999+1));
        }
        
        else if(ch=='2')
        {
        TIM4->CCR1 = 1600;
        printf("\x1B[2J\x1B[H MEDIUM SPEED CCR=%lu Duty=%.2f%%\r\n",TIM4->CCR1,(TIM4->CCR1*100.0f)/(19999+1));
        }
        
        else if(ch=='3')
        {
        TIM4->CCR1 = 2000;
        printf("\x1B[2J\x1B[H HIGH SPEED CCR=%lu Duty=%.2f%%\r\n",TIM4->CCR1,(TIM4->CCR1*100.0f)/(19999+1));
        }
        
        else if(ch=='0')
        {
        TIM4->CCR1 = 1000;
        }
        else
        {
            usart_write_string( USART3, "\n\n Invalid option \n\n");
        } */
        /*
        for(duty =1000;duty<=2000;duty++)
        {
           TIM4->CCR1 = duty; 
           printf("\x1B[2J\x1B[H CCR=%lu Duty=%.2f%%\r\n",TIM4->CCR1,(TIM4->CCR1*100.0f)/(19999+1));
           delay_ms(10);
        }
            TIM4->CCR1 = 2000;
            printf("\x1B[2J\x1B[H CCR=%lu Duty=%.2f%%\r\n",TIM4->CCR1,(TIM4->CCR1*100.0f)/(19999+1));
            delay_ms(5000);

        for(duty =2000;duty>=1000;duty--)
        {
           TIM4->CCR1 = duty; 
           printf("\x1B[2J\x1B[H CCR=%lu Duty=%.2f%%\r\n",TIM4->CCR1,(TIM4->CCR1*100.0f)/(19999+1));
           delay_ms(10);
        }
        */
       /* printf("\n-----------Menu Mode-----------\nA. Calibration \nB.Run\r\n");
       ch = usart_read(USART3);
       usart_write(USART3,ch);
       delay_ms(1000);

       if(ch=='A')
        {
        printf("\n Calibration Started \n Turn off the power supply \n");
        delay_ms(4000);    
        printf("\nUpdating Max throttle value 2000 \n");
        delay_ms(4000);
        TIM4->CCR1 = 2000;            // max position 
        printf("Max Throttle value updated turn on the Supply \n");
        delay_ms(5000);
        
        printf("Updating Min throttle value 1000 \n");
        delay_ms(5000);
        TIM4->CCR1 = 1000;  
        printf("Min Throttle value updated \n"); 
        delay_ms(5000);
        printf("Calibration Completed \n"); 
        delay_ms(2000);
        }
        else if(ch=='B')
        {
        
        usart_write_string( USART3, "\n ----- Select the Option ----- \r\n 0-> OFF \r\n 1-> LOW SPEED \r\n 2-> MEDIUM SPEED \r\n 3-> HIGH SPEED \n");
        ch = usart_read(USART3);
        usart_write(USART3,ch);
        delay_ms(500);

        if(ch=='1')
        {
        TIM4->CCR1 = 1300;
        printf("\x1B[2J\x1B[H LOW SPEED CCR=%lu Duty=%.2f%%\r\n",TIM4->CCR1,(TIM4->CCR1*100.0f)/(19999+1));
        }
        
        else if(ch=='2')
        {
        TIM4->CCR1 = 1600;
        printf("\x1B[2J\x1B[H MEDIUM SPEED CCR=%lu Duty=%.2f%%\r\n",TIM4->CCR1,(TIM4->CCR1*100.0f)/(19999+1));
        }
        
        else if(ch=='3')
        {
        TIM4->CCR1 = 2000;
        printf("\x1B[2J\x1B[H HIGH SPEED CCR=%lu Duty=%.2f%%\r\n",TIM4->CCR1,(TIM4->CCR1*100.0f)/(19999+1));
        }
        
        else if(ch=='0')
        {
        TIM4->CCR1 = 1000;
        }
        else
        {
            usart_write_string( USART3, "\n\n Invalid option \n\n");
        } 
    }
    } 
}

void systick_handler(void)
{
    ticks++;
}

void delay_ms(uint32_t ms)
{
    uint32_t start=ticks;
    while((ticks-start)<ms);
} */ 




////////////////////////////////////////////////////////////


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "stm32f4xx.h"
#include "usart.h"

void delay_ms(uint32_t ms);
void systick_handler(void);
void esc_pwm_init(void);
void usart_init(void);
void usart_write(USART_TypeDef *usart, char c);
void usart_write_string(USART_TypeDef *usart,const char *str);

void ir_exti_init(void);
void ir_timer_init(void); 

char bits[64];
char ch;
uint8_t a=0;

volatile uint32_t previous_time = 0;
volatile uint32_t pulse[128];
volatile uint32_t pulse_index = 0;
volatile uint8_t frame_ready = 0;

volatile uint32_t ticks = 0;

int main(void)
{
    esc_pwm_init();
    usart_init();
    SysTick_Config(16000);
    ir_timer_init();
    ir_exti_init();
    TIM4->CCR1 = 1000;
    delay_ms(4000);
    usart_write_string
    (
        USART3, "\r\n=== IR EXTI Application Started ===\r\n"
    );

    while(1)
    { 

        if(frame_ready)
        {
            uint32_t bit_index = 0;
            for(uint32_t i = 8; i < pulse_index; i += 2)
            {
                if(pulse[i] > 20000)
                {
                    bits[bit_index++] = '1';
                }
                else
                {
                    bits[bit_index++] = '0';
                }
            }
            bits[bit_index] = '\0';
            printf("BITS = %s\r\n", bits);
            
            if(strstr(bits,"111111011011") != NULL)
            {
             TIM4->CCR1 = 1000;
             printf("POWER OFF\r\n");
            }
            else if(strstr(bits,"111111010010") != NULL)
            {
              TIM4->CCR1 = 1100;
              printf("VOL+ DETECTED\r\n");
            }
            else if(strstr(bits,"111111011100") != NULL)
            {
              TIM4->CCR1 = 1400;
              printf("VOL- DETECTED\r\n");
            }
            else if(strstr(bits,"01010010101011") != NULL)
            {
             TIM4->CCR1 = 1600;
             printf("Channel + \r\n");
            }
            else if(strstr(bits,"111010010001011") != NULL)
            {
            TIM4->CCR1 = 1800;
            printf("Channel - \r\n");
            }
            else if(strstr(bits,"101101000100101") != NULL)
            {
            printf("UP DETECTED\r\n");
            }
            else if(strstr(bits,"111101000000101") != NULL)
            {
            printf("DOWN DETECTED\r\n");
            }
            else if(strstr(bits,"100011000111001") != NULL)
            {
            printf("RIGHT DETECTED\r\n");
            }
            else if(strstr(bits,"11111101100110") != NULL)
            {
            printf("LEFT DETECTED\r\n");
            }
           else if(strstr(bits,"11111101101010") != NULL)
            {
              printf("\n ------ OK DETECTED ------ \r\n");

              printf("\n Calibration Started \n Turn off the power supply \n");
              delay_ms(4000);    
              printf("\nUpdating Max throttle value 2000 \n");
              delay_ms(4000);
              TIM4->CCR1 = 2000;            // max position 
              printf("Max Throttle value updated turn on the Supply \n");
              delay_ms(6000);
        
              printf("Updating Min throttle value 1000 \n");
              delay_ms(5000);
              TIM4->CCR1 = 1000;  
              printf("Min Throttle value updated \n"); 
              delay_ms(5000);
              printf("Calibration Completed \n"); 
              delay_ms(2000);
              }
            else
            {
                printf("UNKNOWN BUTTON\r\n");
            } 

            pulse_index = 0;
            frame_ready = 0;
            EXTI->IMR |= (1 << 5);
            }
        
        
    }
}

/* EXTI5 Interrupt Handler */

void exti9_5_handler(void)
{
    if(EXTI->PR & (1 << 5))
    {
        uint32_t now = TIM2->CNT;

        /* First edge */

        if(pulse_index == 0)
        {
            previous_time = now;

            pulse[0] = 0;

            pulse_index = 1;

            EXTI->PR = (1 << 5);

            return;
        }

        if(pulse_index < 128)
        {
            pulse[pulse_index++] =
            now - previous_time;
        }

        previous_time = now;

        /* Frame Complete */

        if(pulse_index >= 68)
        {
            frame_ready = 1;

            EXTI->IMR &= ~(1 << 5);
        }

        EXTI->PR = (1 << 5);
    }
}


void ir_exti_init(void)
{
    // Enable clocks 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    volatile uint32_t dummy;
    dummy = RCC->AHB1ENR;
    dummy = RCC->APB2ENR;
    
    GPIOA->MODER &= ~(3 << (5 * 2));        // PA5 as Input 
    GPIOA->PUPDR &= ~(3 << (5 * 2));        // Enable Pull-up
    GPIOA->PUPDR |=  (1 << (5 * 2));
    SYSCFG->EXTICR[1] &= ~(0xF << 4);       // PA5 -> EXTI5
    EXTI->RTSR |= (1 << 5);                 // Detect both edges
    EXTI->FTSR |= (1 << 5);
    EXTI->IMR |= (1 << 5);                  // Unmask interrupt
    EXTI->PR = (1 << 5);                    // Clear pending flag
    // Enable EXTI5 interrupt 
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void delay_ms(uint32_t ms)
{
    uint32_t start=ticks;
    while((ticks-start)<ms);
} 

void systick_handler(void)
{
    ticks++;
}