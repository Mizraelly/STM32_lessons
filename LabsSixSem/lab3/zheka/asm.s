;constants
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

				; code area
                AREA    |.text| , CODE, READONLY
			    EXPORT Reset_Handler
Reset_Handler   PROC
                B main
                ENDP

				EXTERN main_loop

main PROC
	BL main_loop
	B main ;end loop
	ENDP
	ALIGN

	END