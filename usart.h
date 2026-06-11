#ifndef USART_H
#define USART_H

void usart_init(void);
void usart_write(USART_TypeDef *usart, char c);
void usart_write_string( USART_TypeDef *usart, const char *str);
char usart_read(USART_TypeDef *usart);

#endif