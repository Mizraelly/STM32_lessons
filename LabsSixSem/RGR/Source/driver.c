#include "header.h"


void drive( int *Tacts) {
		//	fix tacts 
		if(*Tacts > 7) *Tacts = 0;
		else if (*Tacts < 0) *Tacts = 7;
	
	switch(*Tacts){
	case 0:
		GPIOC->ODR |= GPIO_ODR_OD9;
		GPIOC->ODR &= ~GPIO_ODR_OD5;
		GPIOC->ODR &= ~GPIO_ODR_OD6;
		GPIOC->ODR &= ~GPIO_ODR_OD8;
	break;
	
	case 1:	
		GPIOC->ODR |= GPIO_ODR_OD9;
		GPIOC->ODR |= GPIO_ODR_OD5;
		GPIOC->ODR &= ~GPIO_ODR_OD6;
		GPIOC->ODR &= ~GPIO_ODR_OD8;	
	break;
	
	case 2:
		GPIOC->ODR &= ~GPIO_ODR_OD9;
		GPIOC->ODR |= GPIO_ODR_OD5;
		GPIOC->ODR &= ~GPIO_ODR_OD6;
		GPIOC->ODR &= ~GPIO_ODR_OD8;	
	break;

	case 3:
		GPIOC->ODR &= ~GPIO_ODR_OD9;
		GPIOC->ODR |= GPIO_ODR_OD5;
		GPIOC->ODR |= GPIO_ODR_OD6;
		GPIOC->ODR &= ~GPIO_ODR_OD8;
	break;
	
	case 4:
		GPIOC->ODR &= ~GPIO_ODR_OD9;
		GPIOC->ODR &= ~GPIO_ODR_OD5;
		GPIOC->ODR |= GPIO_ODR_OD6;
		GPIOC->ODR &= ~GPIO_ODR_OD8;
	break;
	
	case 5:
		GPIOC->ODR &= ~GPIO_ODR_OD9;
		GPIOC->ODR &= ~GPIO_ODR_OD5;
		GPIOC->ODR |= GPIO_ODR_OD6;
		GPIOC->ODR |= GPIO_ODR_OD8;	
	break;

	case 6:
		GPIOC->ODR &= ~GPIO_ODR_OD9;
		GPIOC->ODR &= ~GPIO_ODR_OD5;
		GPIOC->ODR &= ~GPIO_ODR_OD6;
		GPIOC->ODR |= GPIO_ODR_OD8;	
	break;

	case 7:
		GPIOC->ODR |= GPIO_ODR_OD9;
		GPIOC->ODR &= ~GPIO_ODR_OD5;
		GPIOC->ODR &= ~GPIO_ODR_OD6;
		GPIOC->ODR |= GPIO_ODR_OD8;
	break;
	}
}

void enable_step_tim2(){
	//	enable TIM2 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//	set up-count mode
	TIM2->CR1 &= ~TIM_CR1_DIR;

	//	program presceler (Freq_count = Freq_PSC / PSC+1) = 16MHz / (15999+1)  = 1KHz
	TIM2->PSC = 15999;
	//	program auto-reload reg "ARR" (Freq_Event = Freq_count / ARR+1) 
	TIM2->ARR = 14; //	start value, which will be update (ARR = 14 ->  full revolution for the output shaft during 60 sec)
	TIM2->CNT = 0;
	//	enable TIM2 interrupt 
	TIM2->DIER |= TIM_DIER_UIE;
	//	enable preload (shadow register)
	TIM2->CR1 |= TIM_CR1_ARPE;
	//	enable counter 
	TIM2->CR1 |= TIM_CR1_CEN;
	
	NVIC_SetPriority(TIM2_IRQn,1);
	NVIC_ClearPendingIRQ(TIM2_IRQn);
	NVIC_EnableIRQ(TIM2_IRQn); 
	
	
}

