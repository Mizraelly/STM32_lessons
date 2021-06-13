#include "header.h"

int main(void){

  int buttonDec = 0;
  int buttonInc = 0;
  int button_flagDec = 0;
  int button_flagInc = 0;
  int num = 0;
  long sec = 1;
	
  //SETUP
  //Clock enable....................................
  //*RCC_AHB1_ENABLE_REG |= (1 << 0); 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; //включили тактування порту B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; //включили тактування порту C

  //port mode.......................................

  //GPIOC
	GPIOC->MODER &= ~GPIO_MODER_MODE4_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE4_1;
	
	GPIOC->MODER &= ~GPIO_MODER_MODE13_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE13_1;
  
  //GPIOB
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

  
  //DEBUG SevenSeg. LEDs
  debugLed(sec);

  while (1){
	  //Обробка кнопок
	//dec
    buttonDec = 0;
    buttonDec = (!(GPIOC->IDR & GPIO_IDR_ID4)); //PC4
    
    if(0 != ButtonPress(buttonDec,&button_flagDec)){}
    if(0 != ButtonReleased(buttonDec,&button_flagDec)){
      num --;
    }
    fixNumber(&num);
	
	//inc
    buttonInc = 0;
    buttonInc = (!(GPIOC->IDR & GPIO_IDR_ID13)); //PC13 (USER BUTTON 1)
    
    if(0 != ButtonPress(buttonInc,&button_flagInc)){}
    if(0 != ButtonReleased(buttonInc,&button_flagInc)){
      num ++;
    }
	fixNumber(&num);
	
	switchNum(num);
    }
  return 0;
}
