#include "header.h"

void init_gpio () {
	// ports A and C clock enable
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOAEN;
	
	// configure pin A5 to output (mode_bits = 01)
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	GPIOA->MODER &= ~ GPIO_MODER_MODE5_1;
	
	// configure pin PC13 to input (mode_bits = 00)
	// this pin is connected to button
	GPIOC->MODER &= ~ ( GPIO_MODER_MODE13_0 | GPIO_MODER_MODE13_1 );
}

void irq15_10_enable () {
	// SYSCFGREG clock enable
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	// make PC13 as IRQ13 interrupt source
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
	
	// enable 13 interrupt (it is about mask)
	EXTI->IMR |= EXTI_IMR_IM13;
	
	// use positive front (Rising trigger) 
	EXTI->RTSR |= EXTI_RTSR_TR13;	

	/* NVIC(Nested Vectored Interrupt Controller) */
	NVIC_SetPriority(EXTI15_10_IRQn,0); // set highest priority
	NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	// enable all interrupts (CMSIS function) 
	__enable_irq();
}
