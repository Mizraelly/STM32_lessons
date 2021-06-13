; ******* define constants DISCOVERY ***************
RCC_AHB1_BASE				EQU	0x40023800 ; base point of clock-enable register of bus AHB1
GPIOA_BASE					EQU	0x40020000 ; *
GPIOC_BASE					EQU	0x40020800 ; base memory addresses of ports A, C, D
GPIOD_BASE					EQU	0x40020C00 ; *
	
RCC_AHB1_ENR_OFFSET			EQU	0x30 ; clock-enable register offset from rcc_ahb1_base
GPIO_IDR_OFFSET				EQU	0x10 ; *
GPIO_MODER_OFFSET			EQU	0X00 ; GPIO port registers IDR, MODER, ODR, BSRR
GPIO_ODR_OFFSET				EQU	0x14 ; from base memory address of ports A, C, D
GPIOD_BSRR_OFFSET			EQU	0x18 ; *

RCC_AHB1_GPIOA_CLOCK_BIT	EQU 0 ; *
RCC_AHB1_GPIOC_CLOCK_BIT 	EQU	2 ; these bits of register rcc_ahb1_enr respond for ports A, C, D clocking
RCC_AHB1_GPIOD_CLOCK_BIT 	EQU	3 ; *

GPIOD_LED4_PIN_12		 	EQU	12 ;*
GPIOD_LED3_PIN_13		 	EQU	13 ; it is a LED 4...6 at 12...15 pins of port D at board DISCOVERY
GPIOD_LED5_PIN_14		 	EQU	14 ; *
GPIOD_LED6_PIN_15		 	EQU	15 ; *

GPIOC_SW4_PIN_6			 	EQU	6  ;*
GPIOC_SW5_PIN_8			 	EQU	8  ; it is the buttons 1,3,4,5 on pins 6,8,9,11 of port C
GPIOC_SW3_PIN_9			 	EQU	9  ;*
GPIOC_SW1_PIN_11			EQU	11 ;*

GPIOA_LED_PIN_2			 	EQU	2  ;*
GPIOA_LED_PIN_4			 	EQU	4  ;*
GPIOA_LED_PIN_6			 	EQU	6  ; it is pins 2,4,6,7,9,10 of port A, use for connect seven-segment display
GPIOA_LED_PIN_7			 	EQU	7  ;
GPIOA_LED_PIN_9			 	EQU	9  ;
GPIOA_LED_PIN_10			EQU	10 ;		


; Initialize Stack Size
; Equ 400 hex (1024) bytes
Stack_Size      			EQU	0x00000400
	
	END