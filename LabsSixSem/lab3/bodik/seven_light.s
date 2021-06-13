		INCLUDE N_constant.s
	
	AREA	MYCODE, CODE, READONLY
		
		EXPORT numb_one
		EXPORT numb_three
		EXPORT numb_four
		EXPORT numb_five		
		EXPORT numb_zero
		IMPORT button_loop_swt1
		IMPORT button_loop_swt3
		IMPORT button_loop_swt4
		IMPORT button_loop_swt5
					
_light PROC

;Number 1	
numb_one
	LDR R0, =GPIOA_BASE
	LDR R1, [R0, #GPIOD_BSRR_OFFSET]
	
	;first clear seven-segment display (off all segments)
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_2 * 2 + 14))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_4 * 2 + 12))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_6 * 2 + 10))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_7 * 2 + 9))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_9 * 2 + 7))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_10 * 2 + 6))
	STR R1, [R0, #GPIOD_BSRR_OFFSET]	
	
	;on segments, which need to create number 1 
	ORR R1, R1, #(1 << GPIOA_LED_PIN_4)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_6)
	STR R1, [R0, #GPIOD_BSRR_OFFSET]
	B button_loop_swt1

;Number 3
numb_three
	LDR R0, =GPIOA_BASE
	LDR R1, [R0, #GPIOD_BSRR_OFFSET]
	
	;first clear seven-segment display (off all segments)
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_2 * 2 + 14))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_4 * 2 + 12))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_6 * 2 + 10))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_7 * 2 + 9))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_9 * 2 + 7))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_10 * 2 + 6))
	STR R1, [R0, #GPIOD_BSRR_OFFSET]	
	
	;on segments, which need to create number 3	
	ORR R1, R1, #(1 << GPIOA_LED_PIN_7)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_6)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_10)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_4)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_2)
	STR R1, [R0, #GPIOD_BSRR_OFFSET]
	B button_loop_swt3

;Number 4	
numb_four
	LDR R0, =GPIOA_BASE
	LDR R1, [R0, #GPIOD_BSRR_OFFSET]
	
	;first clear seven-segment display (off all segments)	
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_2 * 2 + 14))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_4 * 2 + 12))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_6 * 2 + 10))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_7 * 2 + 9))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_9 * 2 + 7))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_10 * 2 + 6))
	STR R1, [R0, #GPIOD_BSRR_OFFSET]	
	
	;on segments, which need to create number 4	
	ORR R1, R1, #(1 << GPIOA_LED_PIN_9)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_10)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_6)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_4)
	STR R1, [R0, #GPIOD_BSRR_OFFSET]
	B button_loop_swt4
	
;Number 5	
numb_five
	LDR R0, =GPIOA_BASE
	LDR R1, [R0, #GPIOD_BSRR_OFFSET]
	
	;first clear seven-segment display (off all segments)	
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_2 * 2 + 14))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_4 * 2 + 12))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_6 * 2 + 10))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_7 * 2 + 9))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_9 * 2 + 7))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_10 * 2 + 6))
	STR R1, [R0, #GPIOD_BSRR_OFFSET]	
	
	;on segments, which need to create number 5
	ORR R1, R1, #(1 << GPIOA_LED_PIN_7)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_9)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_10)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_4)
	ORR R1, R1, #(1 << GPIOA_LED_PIN_2)
	STR R1, [R0, #GPIOD_BSRR_OFFSET]
	B button_loop_swt5	
	
;Number 0	
numb_zero
	LDR R0, =GPIOA_BASE
	LDR R1, [R0, #GPIOD_BSRR_OFFSET]
	
	;first clear seven-segment display (off all segments)	
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_2 * 2 + 14))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_4 * 2 + 12))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_6 * 2 + 10))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_7 * 2 + 9))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_9 * 2 + 7))
	ORR R1, R1, #(1 << (GPIOA_LED_PIN_10 * 2 + 6))
	STR R1, [R0, #GPIOD_BSRR_OFFSET]	
	
	;on segments, which need to create number 0 (in my situation it is element "-")	
	ORR R1, R1, #(1 << GPIOA_LED_PIN_10)
	STR R1, [R0, #GPIOD_BSRR_OFFSET]
	
	;this is used for go to the next button check
	CMP R3, #1
	BEQ	button_loop_swt3
	CMP R3, #3
	BEQ	button_loop_swt4
	CMP R3, #4
	BEQ	button_loop_swt5
	CMP R3, #5
	BEQ	button_loop_swt1
	
	ENDP
	END
	