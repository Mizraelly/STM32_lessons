// we use STM32F401RETx
#include "header.h"

int wait_time;

int main () {
	
	int i = 0;
	wait_time = wait_time_1;
	
	// init functions
	init_gpio ();
	irq15_10_enable();
	
	// endless loop
	while (1) {
		
		// set bit 5 at port A out_register
		// turn on LED
		GPIOA->BSRR |= GPIO_BSRR_BS5;
			
		// delay
		for (i = 0; i < wait_time; i++);
			
		// reset bit 5 at port A out_register
		// turn off LED
		GPIOA->BSRR |= GPIO_BSRR_BR5;
			
		// delay
		for (i = 0; i < wait_time; i++);
		
	}
}
