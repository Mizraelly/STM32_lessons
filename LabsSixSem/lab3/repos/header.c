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
      case 0: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= ZERO; 
          break;
      case 1: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= ONE; 
          break;
      case 2: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= TWO; 
          break;
	  case 3: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= THREE; 
          break;
	  case 4: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= FOUR; 
          break;
	  case 5: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= FIVE; 
          break;
	  case 6: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= SIX; 
          break;
      case 7: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= SEVEN; 
          break;
      case 8: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= EIGHT; 
          break;
	  case 9: *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
          *GPIOB_OUT_DATA_REG |= NINE; 
          break;	
	}
}

void debugLed(long sec){
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= ZERO; 
  delay(sec);
  
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= ONE;
  delay(sec);
  
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= TWO;
  delay(sec);
  
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= THREE;
  delay(sec);
  
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= FOUR;
  delay(sec);
  
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= FIVE;
  delay(sec);
  
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= SIX;
  delay(sec);
  
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= SEVEN;
  delay(sec);
  
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= EIGHT;
  delay(sec);
  
  *GPIOB_OUT_DATA_REG ^= *GPIOB_OUT_DATA_REG;
  *GPIOB_OUT_DATA_REG |= NINE;
  delay(sec);
 }