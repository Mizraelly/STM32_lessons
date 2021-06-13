#include "stm32f4xx.h" // Device header

#define wait_time_1 500000
#define wait_time_2 2000000

void init_gpio (void);
void irq15_10_enable(void);
void EXTI15_10_IRQHandler(void);
