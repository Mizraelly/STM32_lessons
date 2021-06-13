
#include "ADC.h"


uint16_t ADC_Val[2] = {0,0};

int main ()
{
	ADC_Init();
	ADC_Enable();
	DMA_Init();
	
	DMA_Config((uint32_t) &ADC1->DR, (uint32_t) ADC_Val, 2);
	ADC_Start();
	while(1)
	{
	
	}
}
