#include "header.h"

extern int wait_time;

void EXTI15_10_IRQHandler () {
	// disable this interrupt
	EXTI->IMR &= ~ EXTI_IMR_IM13;
	
	// we have capacitor, so delay is no needed
	
	// change wait_time
	wait_time = wait_time_2 + wait_time_1 - wait_time;
	
	// clear pending bit
	EXTI->PR|= EXTI_PR_PR13;
	
	// enable this interrupt
	EXTI->IMR |= EXTI_IMR_IM13;
}
