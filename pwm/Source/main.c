#include "header.h"
	int sec0, sec1;
	int global;
int main () {
	int i = 0;
	int brightness = 1;
	int stepSize = 1;
	 sec0 = sec1 = 0;
	// init functions
	//init_gpio ();
	//init_systick ();
	//init_timer5();
	//irq0_3_enable ();
	init_gpioA();
	init_tim1_pwm();
	// endless loop
	while (1) {
		if(TIM1->CCR1 >= 700) TIM1->CCR1 = 0;
		TIM1->CCR1 ++;
		for(i = 0; i < 100000; i ++);
		
	}	
}
