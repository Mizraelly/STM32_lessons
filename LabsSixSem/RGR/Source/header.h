#include "stm32f4xx.h"



void init_gpio(void);//	init GPIOx

void drive( int *Tacts);	//driver for step_motor
	
void enable_step_tim2(void); // enable tim2 (step_motor)
void enable_tim_3_4(void);	// enable tim3_4 (HC-SR04)

void irq14_enable (void);	//	enable external interrupt (button)

void EXTI15_10_IRQHandler (void); //	interrupt handler, which responsible for reverse motor
void TIM2_IRQHandler(void);	//	interrupt handler, which responsible for Servo
void TIM4_IRQHandler (void);	//	interrupt handler, which responsible for HC-SR04 pin "Echo"
