	AREA	FUNCTION, CODE, READONLY
    EXPORT sum
sum PROC
		MOV		r2, r0
		MOV		r3, r1
		EOR		r0, r0
		EOR		r1, r1
loop_sign
		LDR		r4, [r2]
		ADDS	r0, r4 
		BVC		pass_ovf
		ADDS	R1, R1, #1
pass_ovf
		ADD		r2, #4
		SUB		r3, #1
		CMP		r3, #0		
		BNE		loop_sign
		BX		lr
		ENDP
		END