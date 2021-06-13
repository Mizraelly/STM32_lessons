#include "header.h"

//	variables for servo_motor	
 int Tacts = 0;
volatile int Step_Dir = 0;
//	variables for HC-SR04
volatile unsigned int distance;
int main(){
	init_gpio();
	enable_step_tim2();
	enable_tim_3_4();
	irq14_enable();
	__enable_irq();

	while(1)
	{	
		//	stall step_drive if distance <= 8 cm
		if(distance <= 8) TIM2->CR1 &= ~TIM_CR1_CEN;
		else 	TIM2->CR1 |= TIM_CR1_CEN;
		
		//	func. step_drive
		drive(&Tacts);
		//	show the distance by led's
		if(distance > 50){
			GPIOB->ODR |= GPIO_ODR_OD1;
			GPIOB->ODR |= GPIO_ODR_OD15;
			GPIOB->ODR |= GPIO_ODR_OD13;} 
		else if (distance > 20){
			GPIOB->ODR |= GPIO_ODR_OD1;
			GPIOB->ODR &= ~GPIO_ODR_OD15;
			GPIOB->ODR |= GPIO_ODR_OD13;} 
		else if (distance > 8){
			GPIOB->ODR &= ~GPIO_ODR_OD1;
			GPIOB->ODR &= ~GPIO_ODR_OD15;
			GPIOB->ODR |= GPIO_ODR_OD13;} 
		else if (distance > 0){
			GPIOB->ODR &= ~GPIO_ODR_OD1;
			GPIOB->ODR &= ~GPIO_ODR_OD15;
			GPIOB->ODR &= ~GPIO_ODR_OD13;
		}
	}
}