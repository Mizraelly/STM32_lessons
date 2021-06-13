; Initialize Stack Size
; Equ 400 hex (1024) bytes
Stack_Size      EQU     0x00000400

; Area STACK (NOINIT and READ/WRITE)
                AREA    STACK, NOINIT, READWRITE, ALIGN=4
; Initialize memory equals Stack_Size
Stack_Mem       SPACE   Stack_Size
__initial_sp

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  Reset_Handler             [WEAK]
__Vectors
                DCD     __initial_sp             ; Top of Stack
                DCD     Reset_Handler            ; Reset Handler
__Vectors_End
				
				AREA    RESULT, DATA, READWRITE			  
			 ALIGN  4				 
QA   		 DCD    0
QL			 DCD    0
	
				AREA    MYDATA, DATA, READONLY
				ALIGN 4	 
X			 EQU		0x15	
Y			 EQU		0x35
Z			 EQU		0x04

A__			 DCD 		0x14
B__			 DCD		0x3F
C__			 DCD		0x1D
D__			 DCD		0x03


				AREA MYCODE, CODE, READONLY		
Reset_Handler   PROC
			LDR R0, =_mainp
			BX 	R0
			ENDP
					
_mainp	PROC
             MOV	R1, #X
			 MOV 	R2, #Y
			 MOV 	R3, #Z
			 
			 LDR	R0, = A__
			 LDR 	R6, [R0]
			 LDR	R0, = B__
			 LDR 	R7, [R0]
			 LDR	R0, = C__
			 LDR 	R8, [R0]
			 LDR	R0, = D__
			 LDR 	R9, [R0]
			 
; Arithmetical calculations  ((X+Y) - Z - (Z-Y))-X = Q 

			 add r4, r1, r2		; r4 = r1+r2 = X + Y
			 sub r4, r4, r3    	; r4 = r4-r3 =(X + Y)-Z
		     sub r5, r3, r2    	; r5 = r3-r2 =(Z - Y) 
		     sub r4, r4, r5    	; r4 = r4-r5 =((X+Y) - Z - (Z-Y))
			 sub r4, r4, r1    	; r4 = r4-r1 = ((X+Y) - Z - (Z-Y))-X = Q

; Logical calculations  Q = (!(A or B or C or D))and(B and (!C) and D xor 0x17 ) , де A=0x14h, B=3Fh, C=1Dh, D=03h

			 orr r10, r6, r7		; r10 = A or B
			 orr r11, r8, r9		; r11 = C or D
			 orr r10, r10, r11		; r10 = A or B or C or D
			 mvn r10, r10			; r10 = !(A or B or C or D)
			 mvn r11, r8			; r11 = !C
			 and r11, r7, r11		; r11 = B and !C
			 and r12, r11, r9		; r12 = B and !C and D
			 eor r11, r12, #0x17	; r11 = B and !C and D xor 0x17
			 and r10, r10, r11      ; r10 = r10 and r11 = (!(A or B or C or D))and(B and !C and D xor 0x17)
			 
;Save results
			 LDR		R0, =QA
			 STR		R4, [R0]
			 LDR		R0, =QL
			 STR		R10, [R0]
__inf_cycle
			 B  __inf_cycle
			 ENDP
END
