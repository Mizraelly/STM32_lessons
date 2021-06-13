#include "header.h"
	int sec0, sec1;
int main () {
	 sec0 = sec1 = 0;
	// init functions
	init_gpio ();
	init_systick ();
	irq0_3_enable ();
	
	// endless loop
	while (1) {
		fixNumber(&sec0, &sec1);
		switchNum(sec0, sec1);
	}
}
