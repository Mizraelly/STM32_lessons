#include "header.h"




void init_gpio()
{
	//	enable GPIOx clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	
//leds
		// (output mode) PB1
	GPIOB->MODER |= GPIO_MODER_MODE1_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE1_1;
	
			// (output mode) PB15
	GPIOB->MODER |= GPIO_MODER_MODE15_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE15_1;
			// (output mode) PB13
	GPIOB->MODER |= GPIO_MODER_MODE13_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE13_1;
	
	// IN1 установка 01(output mode) PC9
	GPIOC->MODER |= GPIO_MODER_MODE9_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE9_1;
	
	// IN2 установка 01(output mode) PC5
	GPIOC->MODER |= GPIO_MODER_MODE5_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE5_1;
	
	// IN3 установка 01(output mode) PC6
	GPIOC->MODER |= GPIO_MODER_MODE6_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE6_1;
	
	// IN4 установка 01(output mode) PC8
	GPIOC->MODER |= GPIO_MODER_MODE8_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE8_1;
	
	// Кнопка 1 установка 00(реверс двигуна) PB14
	GPIOB->MODER &= ~GPIO_MODER_MODE14_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE14_1;
	
	//	set alternative mode for PB4 (TIM3_CH1  - PWM output - pin_trig_HC-SR04)
	GPIOB->MODER &= ~GPIO_MODER_MODE4_0;
	GPIOB->MODER |= GPIO_MODER_MODE4_1;
	//	set alternative function (look at the AF mapping (datasheet))
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL4; 	
	GPIOB->AFR[0] |= GPIO_AFRL_AFRL4_1; //	TIM3-5 AF1
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
	
	//	set alternative mode for PB6 (TIM4_CH1 - Capture input mode - pin_Echo_HC-SR04)
	GPIOB->MODER &= ~GPIO_MODER_MODE6_0;
	GPIOB->MODER |= GPIO_MODER_MODE6_1;
	//	set alternative function 
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL6;
	GPIOB->AFR[0] |= GPIO_AFRL_AFRL6_1;	//	TIM3-5 AF1

}

void irq14_enable () {
	// SYSCFGREG clock enable
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	// make PB(14) as IRQ interrupt source
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI14_PB;
	
	// enable (0-3) interrupt (it is about mask)
	EXTI->IMR |= EXTI_IMR_IM14;
	
	// use positive front (Rising trigger) 
	EXTI->RTSR |= EXTI_RTSR_TR14;
		
	/* NVIC(Nested Vectored Interrupt Controller) */
	// set priorities

	NVIC_SetPriority(EXTI15_10_IRQn,1);
	// clear pendings
	NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	// enable interrupts
	NVIC_EnableIRQ(EXTI15_10_IRQn); 
}




