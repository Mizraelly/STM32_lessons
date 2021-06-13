#include "header.h"
//variables for Servo_motor
extern  int Tacts;
extern volatile int Step_Dir;

//variables for HC-SR04
volatile unsigned int pulse_width;
volatile unsigned int current_captured, last_captured = 0;
volatile unsigned int signal_polarity = 0; //	need to separate High and Low front
extern volatile unsigned int distance;

// EXTI14_IRQ is responsible for revers step motor
void EXTI15_10_IRQHandler () {	
	//	if execute Interrupt for PB14
	if(EXTI->PR & EXTI_PR_PR14){ 
	//	disable this interrupt
	EXTI->IMR &= ~ EXTI_IMR_IM14;

	//	reverse step_motor_direction
	Step_Dir = !Step_Dir;
	// clear pending bit
	EXTI->PR|= EXTI_PR_PR14;
		
	//	enable this interrupt
	EXTI->IMR |= EXTI_IMR_IM14;
	}
}

//	responsible for Servo
void TIM2_IRQHandler(){
	//	increment of dec. tacts, which needed for step_driver (include reverse)
	if(TIM2->SR & TIM_SR_UIF){
		if(Step_Dir) Tacts --;
		else Tacts++;
	//	calibrate Speed for step_motor
	if(distance > 350) distance = 350;
	TIM2->ARR = 30 - (distance * 30 / 400);	
	//	clear_update_interrupt_flag
	TIM2->SR &= ~TIM_SR_UIF;
	}
}


//	responsible for HC-SR04 pin "Echo"
void TIM4_IRQHandler(){
	if(TIM4->SR & TIM_SR_CC1IF){ // if execute interrupt for CH1 (both edges)
		current_captured = TIM4->CCR1;
		signal_polarity = 1 - signal_polarity; // reverse polarity
		if(!signal_polarity){ // if polarity = LOW -> Falling edge
			if(current_captured > last_captured ) {
				pulse_width = current_captured - last_captured; //	calc pulse_width
				distance = pulse_width / 59;	// distance = (pulse_time * speed of sound)/2
			}
			else if (last_captured > current_captured) { //	take into account counter overflow
				pulse_width = (0xFFFF - last_captured) + current_captured;
				distance = pulse_width / 59;	// distance = (pulse_time * speed of sound)/2
			}
		}
		last_captured = current_captured; //	if fall edge not detected
		
	}
		if(TIM4->SR & TIM_SR_UIF) 
		//	clear_update_interrupt_flag
		TIM4->SR &= ~TIM_SR_UIF;

}