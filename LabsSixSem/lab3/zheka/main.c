#include "header.h"
	
void main_loop(){
  int buttonDec = 0;
  int buttonInc = 0;
  int button_flagDec = 0;
  int button_flagInc = 0;
  int num = 0;
  long sec = 1;
	
  //SETUP
  //Clock enable....................................
  *RCC_AHB1_ENABLE_REG |= (1 << 0); //включили тактування порту A
  *RCC_AHB1_ENABLE_REG |= (1 << 1); //включили тактування порту B

  
  //port mode.......................................
  //GPIOA
  GPIOx_SET_MODE_INPUT(A,0);
  GPIOx_SET_MODE_INPUT(A,15);
  
  //GPIOB
  GPIOx_SET_MODE_OUTPUT(B,0);
  GPIOx_SET_MODE_OUTPUT(B,1);
  GPIOx_SET_MODE_OUTPUT(B,2);
  GPIOx_SET_MODE_OUTPUT(B,3);
  GPIOx_SET_MODE_OUTPUT(B,4);
  GPIOx_SET_MODE_OUTPUT(B,5);
  GPIOx_SET_MODE_OUTPUT(B,6);
  
  //DEBUG SevenSeg. LEDs
  debugLed(sec);

  while (1){
	  //Обробка кнопок
	//dec
    buttonDec = 0;
    buttonDec = (1 == (*GPIOA_IN_DATA_REG & (1 << 0))); //PA0 (USER BUTTON)
    
    if(0 != ButtonPress(buttonDec,&button_flagDec)){}
    if(0 != ButtonReleased(buttonDec,&button_flagDec)){
      num --;
    }
    fixNumber(&num);
	
	//inc
    buttonInc = 0;
    buttonInc = (0 == (*GPIOA_IN_DATA_REG & (1 << 15))); //PA15 (External button)
    
    if(0 != ButtonPress(buttonInc,&button_flagInc)){}
    if(0 != ButtonReleased(buttonInc,&button_flagInc)){
      num ++;
    }
	fixNumber(&num);
	
	switchNum(num);
    }
 }  