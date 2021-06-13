#include "header.h"

int ButtonPress (const int but, int *but_flag){
	int i = 0;
	if (but == 1 && *but_flag == 0){
		for(i = 0; i < 1000000; i ++){}
		
		*but_flag = 1;
		return 1;
	}
	return 0;
}

int ButtonReleased (const int but, int *but_flag){
	int i = 0;
	if (but == 0 && *but_flag == 1){
		for(i = 0; i < 1000000; i ++){}
		
		*but_flag = 0;
		return 1;
	}
	return 0;
}

void delay (long sec){
	long i = 0;
	for ( i = 0; i < sec * 4000000; i ++){}
}

void fixNumber(int *num){
	if(*num > 9) *num = 0;
	if(*num < 0) *num = 9;
}

void switchNum(int num){
	switch(num) {
      case 0:GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= ZERO; 
          break;
      case 1: GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= ONE; 
          break;
      case 2: GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= TWO; 
          break;
	  case 3: GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= THREE; 
          break;
	  case 4: GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= FOUR; 
          break;
	  case 5: GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= FIVE; 
          break;
	  case 6: GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= SIX; 
          break;
      case 7: GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= SEVEN; 
          break;
      case 8: GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= EIGHT; 
          break;
	  case 9: GPIOB->ODR ^= GPIOB->ODR;
          GPIOB->ODR |= NINE; 
          break;	
	}
}

void debugLed(long sec){
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= ZERO; 
  delay(sec);
  
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= ONE;
  delay(sec);
  
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= TWO;
  delay(sec);
  
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= THREE;
  delay(sec);
  
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= FOUR;
  delay(sec);
  
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= FIVE;
  delay(sec);
  
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= SIX;
  delay(sec);
  
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= SEVEN;
  delay(sec);
  
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= EIGHT;
  delay(sec);
  
  GPIOB->ODR ^= GPIOB->ODR;
  GPIOB->ODR |= NINE;
  delay(sec);
 }
