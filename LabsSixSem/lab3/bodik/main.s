		INCLUDE N_constant.s
	
	AREA	MYCODE, CODE, READONLY
		
		EXPORT _main				
		EXPORT button_loop_swt1
		EXPORT button_loop_swt3
		EXPORT button_loop_swt4
		EXPORT button_loop_swt5
		IMPORT numb_one				
		IMPORT numb_three
		IMPORT numb_four
		IMPORT numb_five		
		IMPORT numb_zero
				
			
_main	PROC

; enable clock for GPIO ports A, C, D
	LDR R0, = RCC_AHB1_BASE
	LDR R1, [R0, #RCC_AHB1_ENR_OFFSET]
	ORR R1, R1, #(1 << RCC_AHB1_GPIOA_CLOCK_BIT)
	ORR R1, R1, #(1 << RCC_AHB1_GPIOC_CLOCK_BIT)
	ORR R1, R1, #(1 << RCC_AHB1_GPIOD_CLOCK_BIT)
	STR R1, [R0, #RCC_AHB1_ENR_OFFSET]

; set output mode for PD 12...15
	LDR R0, =GPIOD_BASE
	LDR R1, [R0, #GPIO_MODER_OFFSET]
	ORR R1, R1, #(1 << (GPIOD_LED4_PIN_12 * 2))
	BIC R1, R1, #(1 << (GPIOD_LED4_PIN_12 * 2 + 1))
	
	ORR R1, R1, #(1 << (GPIOD_LED3_PIN_13 * 2))
	BIC R1, R1, #(1 << (GPIOD_LED3_PIN_13 * 2 + 1))
	
	ORR R1, R1, #(1 << (GPIOD_LED5_PIN_14 * 2))
	BIC R1, R1, #(1 << (GPIOD_LED5_PIN_14 * 2 + 1))
	
	ORR R1, R1, #(1 << (GPIOD_LED6_PIN_15 * 2))
	BIC R1, R1, #(1 << (GPIOD_LED6_PIN_15 * 2 + 1))
	STR R1, [R0, #GPIO_MODER_OFFSET]

; set input mode for PC 6,8,9,11
	LDR R0, =GPIOC_BASE
	LDR R1, [R0, #GPIO_MODER_OFFSET]
	BIC R1, R1, #(1 << (GPIOC_SW4_PIN_6 * 2))
	BIC R1, R1, #(1 << (GPIOC_SW4_PIN_6 * 2 + 1))
	
	BIC R1, R1, #(1 << (GPIOC_SW5_PIN_8 * 2))
	BIC R1, R1, #(1 << (GPIOC_SW5_PIN_8 * 2 + 1))

	BIC R1, R1, #(1 << (GPIOC_SW3_PIN_9 * 2))
	BIC R1, R1, #(1 << (GPIOC_SW3_PIN_9 * 2 + 1))
	
	BIC R1, R1, #(1 << (GPIOC_SW1_PIN_11 * 2))
	BIC R1, R1, #(1 << (GPIOC_SW1_PIN_11 * 2 + 1))
	STR R1, [R0, #GPIO_MODER_OFFSET]

; set output mode for PA 2,4,6,7,9,10
	LDR R0, =GPIOA_BASE
	LDR R1, [R0, #GPIO_MODER_OFFSET]
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_2 * 2))
	BIC R1, R1, #(1 << (GPIOA_LED_PIN_2 * 2 + 1))
	
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_4 * 2))
	BIC R1, R1, #(1 << (GPIOA_LED_PIN_4 * 2 + 1))
	
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_6 * 2))
	BIC R1, R1, #(1 << (GPIOA_LED_PIN_6 * 2 + 1))
	
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_7 * 2))
	BIC R1, R1, #(1 << (GPIOA_LED_PIN_7 * 2 + 1))
	
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_9 * 2))
	BIC R1, R1, #(1 << (GPIOA_LED_PIN_9 * 2 + 1))
	
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_10 * 2))
	BIC R1, R1, #(1 << (GPIOA_LED_PIN_10 * 2 + 1))
	STR R1, [R0, #GPIO_MODER_OFFSET]

;check value in IDR register, port PC 9
;if IDR PC9 = 1, it is means that button not pressed => set 1 on 29 bit, in register BSSR PD13
;branch to numb_three, for set number three on seven_segment display

;else (IDR PC9 = 0), it is means that button pressed => set 1 on 13 bit, in register BSSR PD13
;branch to numb_zero, for set number zero (in my situation it is element "-") on seven_segment display
;SWT3 (PIN9, LED3)/////////////////////////////////////////////
button_loop_swt3
	LDR R0, =GPIOC_BASE
	LDR R2, =GPIOD_BASE
	LDR R1, [R0, #GPIO_IDR_OFFSET]
	LDR R3, [R2, #GPIOD_BSRR_OFFSET]
	TST R1, #(1 << GPIOC_SW3_PIN_9)
	BNE set_null_swt3
	ORR R3, R3, #(1 << (GPIOD_LED3_PIN_13))
	STR R3, [R2, #GPIOD_BSRR_OFFSET]
	B numb_three

set_null_swt3
	ORR R3, R3, #(1 << (GPIOD_LED3_PIN_13 * 2 + 3))
	STR R3, [R2, #GPIOD_BSRR_OFFSET]
	MOV R3, #3
	B numb_zero	
	
;check value in IDR register, port PC 8
;if IDR PC8 = 1, it is means that button not pressed => set 1 on 28 bit, in register BSSR PD12
;branch to numb_five, for set number five on seven_segment display

;else (IDR PC8 = 0), it is means that button pressed => set 1 on 12 bit, in register BSSR PD12
;branch to numb_zero, for set number zero (in my situation it is element "-") on seven_segment display	
;SWT5 (PIN8, LED4)/////////////////////////////////////////////
button_loop_swt5
	LDR R0, =GPIOC_BASE
	LDR R2, =GPIOD_BASE
	LDR R1, [R0, #GPIO_IDR_OFFSET]
	LDR R3, [R2, #GPIOD_BSRR_OFFSET]
	TST R1, #(1 << GPIOC_SW5_PIN_8)
	BNE set_null_swt5
	ORR R3, R3, #(1 << (GPIOD_LED4_PIN_12))
	STR R3, [R2, #GPIOD_BSRR_OFFSET]
	B numb_five

set_null_swt5
	ORR R3, R3, #(1 << (GPIOD_LED4_PIN_12 * 2 + 4))
	STR R3, [R2, #GPIOD_BSRR_OFFSET]
	MOV R3, #5
	B numb_zero	

;check value in IDR register, port PC 11
;if IDR PC11 = 1, it is means that button not pressed => set 1 on 31 bit, in register BSSR PD15
;branch to numb_one, for set number one on seven_segment display

;else (IDR PC11 = 0), it is means that button pressed => set 1 on 15 bit, in register BSSR PD15
;branch to numb_zero, for set number zero (in my situation it is element "-") on seven_segment display
;SWT1 (PIN9, LED6)/////////////////////////////////////////////
button_loop_swt1
	LDR R0, =GPIOC_BASE
	LDR R2, =GPIOD_BASE
	LDR R1, [R0, #GPIO_IDR_OFFSET]
	LDR R3, [R2, #GPIOD_BSRR_OFFSET]
	TST R1, #(1 << GPIOC_SW1_PIN_11)
	BNE set_null_swt1
	ORR R3, R3, #(1 << (GPIOD_LED6_PIN_15))
	STR R3, [R2, #GPIOD_BSRR_OFFSET]
	B numb_one

set_null_swt1
	ORR R3, R3, #(1 << (GPIOD_LED6_PIN_15 * 2 + 1))
	STR R3, [R2, #GPIOD_BSRR_OFFSET]
	MOV R3, #1
	B numb_zero	

;check value in IDR register, port PC 6
;if IDR PC6 = 1, it is means that button not pressed => set 1 on 30 bit, in register BSSR PD14
;branch to numb_four, for set number four on seven_segment display

;else (IDR PC6 = 0), it is means that button pressed => set 1 on 14 bit, in register BSSR PD14
;branch to numb_zero, for set number zero (in my situation it is element "-") on seven_segment display
;SWT4 (PIN6, LED5)/////////////////////////////////////////////
button_loop_swt4
	LDR R0, =GPIOC_BASE
	LDR R2, =GPIOD_BASE
	LDR R1, [R0, #GPIO_IDR_OFFSET]
	LDR R3, [R2, #GPIOD_BSRR_OFFSET]
	TST R1, #(1 << GPIOC_SW4_PIN_6)
	BNE set_null_swt4
	ORR R3, R3, #(1 << (GPIOD_LED5_PIN_14))
	STR R3, [R2, #GPIOD_BSRR_OFFSET]
	B numb_four

set_null_swt4
	ORR R3, R3, #(1 << (GPIOD_LED5_PIN_14 * 2 + 2))
	STR R3, [R2, #GPIOD_BSRR_OFFSET]
	MOV R3, #4
	B numb_zero	


	ENDP
	END
	