
#include "ADC.h"

uint16_t delay = 10000;
extern int ADC_val[2];

void ADC_Init(void)
{
	//1. Enable ADC and GPIO clock (ADC1_IN1 - PA1)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;	//	enable GPIOA_clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;		//	enable ADC1_clock
	
	//2. Set the prescaler in the Common control register (CCR) (MAX_freq_ADC = 36 MHz, PCLK2 = 16 MHz,so -> PCS = 0)
	ADC->CCR &= ~ADC_CCR_ADCPRE; //	PCLK2 not
	
	//3. Set the Scan mode and resolution in the Control reg. 1 (CR1)
	ADC1->CR1 |= ADC_CR1_SCAN; //	Scan mode enable
	ADC1->CR1 &= ~ADC_CR1_RES; //	Select 12-bit ADC1
	
	//4. Set the Continuius Conversion, EOC and Data Alignment in Control reg.2 (CR2)
	ADC1->CR2 |= ADC_CR2_CONT; //	Set cont. mode
	ADC1->CR2 |= ADC_CR2_EOCS; // 	Enable End of conversion (EOC) SR->EOC bit set at the end of each regular conversion
	ADC1->CR2 &= ~ADC_CR2_ALIGN; //	Data alignment RIGHT
	
	//5. Set the sampling Time for the channels in ADC_SMPRx Tcont = (Samp_time + Cycles(12 for 401re)) / Freq_APB2
	ADC1->SMPR2 &= ~ADC_SMPR2_SMP1; //	Set Samp.time for ADC1_IN1 = 3 cycles  (Tcont = (3+12)/16MHz = 9,37 * 10^-7 second == 0,97 microsec )
	
	//6. Set the regilar channel sequance length in ADC_SQR1
	//ADC1->SQR1 &= ~ADC_SQR1_L; //	SQR1_L = 0 for 1  seq. conversion
	ADC1->SQR1 |= ADC_SQR1_L_0; //	SQR1_L = 1 for 2  seq. conversion
	
	//7. Set the Respective GPIO PINs in the Analog mode
	GPIOA->MODER |= GPIO_MODER_MODE1; //	set Analog mode (2'b11) for PA1
	GPIOA->MODER |= GPIO_MODER_MODE4; //	set Analog mode (2'b11) for PA4
	
	//Add DMA ...
	//8. Enable DMA
	ADC1->CR2 |= ADC_CR2_DMA; //	Enable DMA
	ADC1->CR2 |= ADC_CR2_DDS; //	Select continuous request
	
	//9. Set Channel Sequance
	ADC1->SQR3 |= (1 << 0); //	Seq.1 - channel 1
	ADC1->SQR3 |= (4 << 5); //	Seq.2 - channel 4
	
	
	//x. Enable EOC interrupt
	//ADC1->CR1 |= ADC_CR1_EOCIE;
	/*
	NVIC_SetPriority(ADC_IRQn, 1);
	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_EnableIRQ(ADC_IRQn);
	*/
	
}	

void ADC_Enable(void)
{
	//1. Enable the ADC by setting ADON bit in CR2
	ADC1->CR2 |= ADC_CR2_ADON;	//	Enable ADC
	
	//2. Wait for ADC to stabilize  
	while (delay--); //	wait for stab.
}

void ADC_Start(void)
{
	//1. Clear status register
	ADC1->SR = 0;
	
	//2. Start the Conversion by setting the SWSTART bit in CR2
	ADC1->CR2 |= ADC_CR2_SWSTART; //	start the conversion
}

void ADC_WaitForConv(void)
{
	//1. Wait, for EOC flag to set
	while (!(ADC1->SR & ADC_SR_EOC));
	
}

int ADC_get_Val(void)
{
	return ADC1->DR; //	Read the Data register
}

void ADC_Disable(void)
{
	//1. Disable ADC by clearing ADON bit in CR2
	ADC1->CR2 &= ~ADC_CR2_ADON;
}

void DMA_Init(void)
{
	//1. Enable DMA2 clock
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	
	//2. Select the Data Direction (DMA2_Stream0 - channel 0 -> ADC1)
	DMA2_Stream0->CR &= ~DMA_SxCR_DIR; //	Select Periph->Mem direction
	
	//3. Select the Circular mode (DMA2_Stream0->NDTR will never be 0)
	DMA2_Stream0->CR |= DMA_SxCR_CIRC; //	Enable circular mode
	
	//4. Enable Memory Address Increment
	DMA2_Stream0->CR |= DMA_SxCR_MINC; //	Enable increment memory address pointer after each data transfer
	
	//5. Select Periph/Mem data size by 16 bit (2'01)
	DMA2_Stream0->CR |= DMA_SxCR_PSIZE_0; //	Select periph. data size by 16 bit
	DMA2_Stream0->CR |= DMA_SxCR_MSIZE_0; //	Select mem. data size by 16 bit
	
	//6. Select channel (DMA2_Stream0 - channel 0 -> ADC1)
	DMA2_Stream0->CR &= ~DMA_SxCR_CHSEL; //	Select channel 0
}

void DMA_Config(uint32_t srcAdd, uint32_t destAdd, uint8_t size)
{
	//1. Assign number of data transaction
	DMA2_Stream0->NDTR = size; // set num. of data transaction
	
	//2. Assign source address (Periph.)
	DMA2_Stream0->PAR = srcAdd;
	
	//3. Assign destination address (Mem.)
	DMA2_Stream0->M0AR = destAdd;
	
	//4. Enable the DMA Stream 
	DMA2_Stream0->CR |= DMA_SxCR_EN;
}
