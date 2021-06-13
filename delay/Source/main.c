#include "header.h"
	int sec0, sec1;
int main () {
	int i = 0;
	 sec0 = sec1 = 0;
	// init functions
	init_gpio ();
	//init_systick ();
	init_timer5();
	//irq0_3_enable ();

	
	// endless loop
	while (1) {
		sec1 = 0;
		for (i = 0; i < 10; i ++){
			fixNumber(&sec0, &sec1);
			switchNum(sec0, sec1);
			delay(1000);
			sec1 ++;
		}
	}
}
