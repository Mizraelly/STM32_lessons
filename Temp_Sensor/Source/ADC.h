
#include "stm32f4xx.h"



void ADC_Init(void);
void ADC_Enable(void);
void ADC_Start(void);
void ADC_WaitForConv(void);
int ADC_get_Val(void);
void ADC_Disable(void);

//void ADC_IRQHandler(void);

void DMA_Init(void);
void DMA_Config(uint32_t srcAdd, uint32_t destAdd, uint8_t size);
