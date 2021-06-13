#include "header.h"
extern int sec0, sec1;
// EXTI0_IRQ is responsible for the reset time
void EXTI0_IRQHandler () {
	// disable this interrupt
	EXTI->IMR &= ~ EXTI_IMR_IM0;
	
	// change time
	sec0 = sec1 = 0;
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = (FREQ_DIV_VAL - 1);
	
	// clear pending bit
	EXTI->PR|= EXTI_PR_PR0;
	
	// enable this interrupt
	EXTI->IMR |= EXTI_IMR_IM0;
}

// EXTI1_IRQ is responsible for stop timer
void EXTI1_IRQHandler () {
	// disable this interrupt
	EXTI->IMR &= ~ EXTI_IMR_IM1;
	
	// stop systick
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	
	// clear pending bit
	EXTI->PR|= EXTI_PR_PR1;
	
	// enable this interrupt
	EXTI->IMR |= EXTI_IMR_IM1;
}

// EXTI2_IRQ is responsible for start timer
void EXTI2_IRQHandler () {
	// disable this interrupt
	EXTI->IMR &= ~ EXTI_IMR_IM2;
	
	// start sstick
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	// clear pending bit
	EXTI->PR|= EXTI_PR_PR2;
	
	// enable this interrupt
	EXTI->IMR |= EXTI_IMR_IM2;
}

// EXTI3_IRQ is responsible for stop timer
void EXTI3_IRQHandler () {
	// disable this interrupt
	EXTI->IMR &= ~ EXTI_IMR_IM3;
	
	// start sstick
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	
	// clear pending bit
	EXTI->PR|= EXTI_PR_PR3;
	
	// enable this interrupt
	EXTI->IMR |= EXTI_IMR_IM3;
}

void SysTick_Handler() {
	sec0++;
}