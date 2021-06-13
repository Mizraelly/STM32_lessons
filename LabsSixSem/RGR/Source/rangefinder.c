#include "header.h"




void enable_tim_3_4(){
	//enable TIM3_4 clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM4EN;  

	//	select up-count mode
	TIM3->CR1 &= ~TIM_CR1_DIR;
	//	program prescaler Count_Freq = PCLK / (PSC + 1) => 16MHz/(159+1) = 100KHz == 0.1 MHz == 10 microsec (period)
	TIM3->PSC = 159;
	//	program ARR, max_value, OCH_Freq = Count_Freq / (ARR + 1) => 100KHz / (65534+1) = 1,52 Hz == 0,655 seconds (period)
	TIM3->ARR = 65534;
	//	select PWM mode 1 on channel 1 OCREF = HIGH if CNT < CCR else LOW (3'b110)
	TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 ;
	//	enable register preload (change to CCR1 take effect at UEV event)
	TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
	//	enable auto reload-preload register
	TIM3->CR1 |= TIM_CR1_ARPE;
	//	select output polarity (CC1P in TIM1_CCER1) 0 - active high , 1 - act. low
	TIM3->CCER &= ~TIM_CCER_CC1P;
	//	enable complementary output of CH1 (CC1E bit TIM1->CCER)
	TIM3->CCER |=  TIM_CCER_CC1E;

	//	enable all outputs (Main output enable in in TIM3->BDTR) 1 - enable, 0 - disable
	TIM3->BDTR |= TIM_BDTR_MOE;
	//	select duty cycle 
	TIM3->CCR1 = 1; // pulse width = 10 microsec 
	//	enable counter of ch1
	TIM3->CR1 |= TIM_CR1_CEN;
	
	
	//	program prescaler Count_Freq = 1 MHz (PSC = 15)
	TIM4->PSC = 15;				
	//	set max value ARR
	TIM4->ARR = 0xFFFF;					
	//	set_up-count mode
	TIM4->CR1 &= ~TIM_CR1_DIR;
	//	config CH1 as input
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S;	
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;
	//	disable digit filter
	TIM4->CCMR1 &= ~TIM_CCMR1_IC1F; 	
	//	set active both edges
	TIM4->CCER |= TIM_CCER_CC1P | TIM_CCER_CC1NP; 
	//	disable input capture prescaler
	TIM4->CCMR1 &= ~TIM_CCMR1_IC1PSC; 	
	//	enable input capture CH1
	TIM4->CCER |= TIM_CCER_CC1E;		
	//	enable interrupt for CH1
	TIM4->DIER |= TIM_DIER_CC1IE;	
	//	enable TIM4 counter
	TIM4->CR1 |= TIM_CR1_CEN;			
	  
	NVIC_SetPriority(TIM4_IRQn,0);
	NVIC_ClearPendingIRQ(TIM4_IRQn);
	NVIC_EnableIRQ(TIM4_IRQn); 
	
}