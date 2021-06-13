#include "header.h"

void init_gpio () {
	// ports B and C clock enable
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
	
	// configure pin C(0-3) to input (mode_bits = 00)
	GPIOC->MODER &= ~(GPIO_MODER_MODE0_0|GPIO_MODER_MODE0_1);
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE1_0|GPIO_MODER_MODE1_1);
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE2_0|GPIO_MODER_MODE2_1);
	
	GPIOC->MODER &= ~(GPIO_MODER_MODE3_0|GPIO_MODER_MODE3_1);
  
	// configure pin B(0-8) to output (mode_bits = 01)
	GPIOB->MODER |= GPIO_MODER_MODE0_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE0_1;
  
	GPIOB->MODER |= GPIO_MODER_MODE1_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE1_1;
  
	GPIOB->MODER |= GPIO_MODER_MODE2_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE2_1;
  
	GPIOB->MODER |= GPIO_MODER_MODE3_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE3_1;
  
	GPIOB->MODER |= GPIO_MODER_MODE4_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE4_1;
  
	GPIOB->MODER |= GPIO_MODER_MODE5_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE5_1;
  
	GPIOB->MODER |= GPIO_MODER_MODE6_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE6_1;

	GPIOB->MODER |= GPIO_MODER_MODE7_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE7_1;
  
	GPIOB->MODER |= GPIO_MODER_MODE8_0;
	GPIOB->MODER &= ~GPIO_MODER_MODE8_1;

}

void irq0_3_enable () {
	// SYSCFGREG clock enable
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	// make PC(0-3) as IRQ interrupt source
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PC;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI1_PC;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PC;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PC;
	
	// enable (0-3) interrupt (it is about mask)
	EXTI->IMR |= EXTI_IMR_IM0;
	EXTI->IMR |= EXTI_IMR_IM1;
	EXTI->IMR |= EXTI_IMR_IM2;
	EXTI->IMR |= EXTI_IMR_IM3;
	
	// use positive front (Rising trigger) 
	EXTI->RTSR |= EXTI_RTSR_TR0;
	EXTI->RTSR |= EXTI_RTSR_TR1;
	EXTI->RTSR |= EXTI_RTSR_TR2;
	EXTI->RTSR |= EXTI_RTSR_TR3;
		
	/* NVIC(Nested Vectored Interrupt Controller) */
	// set priorities
	NVIC_SetPriority(EXTI0_IRQn,0); // set highest priority
	NVIC_SetPriority(EXTI1_IRQn,1);
	NVIC_SetPriority(EXTI2_IRQn,2);
	NVIC_SetPriority(EXTI3_IRQn,3);
	
	// clear pendings
	NVIC_ClearPendingIRQ(EXTI0_IRQn);
	NVIC_ClearPendingIRQ(EXTI1_IRQn);
	NVIC_ClearPendingIRQ(EXTI2_IRQn);
	NVIC_ClearPendingIRQ(EXTI3_IRQn);
	
	// enable interrupts
	NVIC_EnableIRQ(EXTI0_IRQn); 
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	
	// enable all interrupts (CMSIS function) 
	__enable_irq();
}

void init_systick(){
	// Reset Systick
	SysTick->CTRL = 0;
	
	// Value which load to counter after overflow
	SysTick->LOAD = (FREQ_DIV_VAL - 1);
	
	// Value from which count to LOAD
	SysTick->VAL = 0;
	
	// Set bits of regsiter SYSTICK_CTRL
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;	
}

void init_timer5() {
	//	enable timer 5 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	//	disable timer 5
	TIM5->CR1 &= TIM_CR1_CEN;
	//	set up-counting mode (0 - up , 1 - down)
	TIM5->CR1 &= TIM_CR1_DIR;
	//	clear status register	
	TIM5->SR = 0;
	//	clear counter
	TIM5->CNT = 0;
	//	fill presceler register (make 1 KHz)
	TIM5->PSC = 15999; //Freq(OutPSC)=Freq(InPSC)/(PSC-1) => 16 MHz/(16000-1)=1KHz 
}

void delay (uint16_t ms) {
	if(ms == 0) return;
	//	disable timer 5
	TIM5->CR1 &= TIM_CR1_CEN;
	//	clear status register	
	TIM5->SR = 0;
	//	clear counter
	TIM5->CNT = 0;
	//	write delay ms in auto-reload register (ARR)
	TIM5->ARR = ms - 1;
	//	enable tim5
	TIM5->CR1 |= TIM_CR1_CEN;
	
	while ((TIM5->SR & TIM_SR_UIF) == 0);
	
}

void switchNum(int sec0, int sec1){
	int num = 0;
	int i = 0;
	
	for(i = 0; i < 2; i ++){
		GPIOB->ODR ^= GPIOB->ODR;
		switch (i){
			case 0: GPIOB->ODR |= (1 << 7); 
			num = sec0;
			break;
			
			case 1: GPIOB->ODR |= (1 << 8); 
			num = sec1;
			break;
		}
		
		switch(num) {
		  case 0:
			  GPIOB->ODR |= ZERO; 
			  break;
		  case 1: 
			  GPIOB->ODR |= ONE; 
			  break;
		  case 2: 
			  GPIOB->ODR |= TWO; 
			  break;
		  case 3: 
			  GPIOB->ODR |= THREE; 
			  break;
		  case 4: 
			  GPIOB->ODR |= FOUR; 
			  break;
		  case 5: 
			  GPIOB->ODR |= FIVE; 
			  break;
		  case 6: 
			  GPIOB->ODR |= SIX; 
			  break;
		  case 7: 
			  GPIOB->ODR |= SEVEN; 
			  break;
		  case 8: 
			  GPIOB->ODR |= EIGHT; 
			  break;
		  case 9: 
			  GPIOB->ODR |= NINE; 
			  break;	
		  }
	}
}

void fixNumber(int *sec0, int *sec1){
	if(*sec0 > 9) {
		*sec0 = 0;
		*sec1 += 1;
	}
	
	if(*sec0 < 0){
		*sec0 = 9;
		*sec1 -= 1;
	}
}
