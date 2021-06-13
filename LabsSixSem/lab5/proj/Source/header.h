#include "stm32f4xx.h" 


#define FREQ_DIV_VAL 16000000

//constants
#define ZERO 63
#define ONE	6
#define TWO	91
#define THREE 79
#define FOUR 102
#define FIVE 109
#define SIX 125
#define SEVEN 7
#define EIGHT 127
#define NINE 111

void fixNumber(int *sec0, int *sec1);
void switchNum(int sec0, int sec1);


void init_gpio (void);
void init_systick(void);
void irq0_3_enable (void);

void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);

void SysTick_Handler(void);

