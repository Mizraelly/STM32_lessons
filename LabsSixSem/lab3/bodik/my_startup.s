		INCLUDE N_constant.s

				AREA    STACK, NOINIT, READWRITE, ALIGN=4
Stack_Mem       SPACE   Stack_Size
__initial_sp


				AREA	RESET, DATA, READONLY
				EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size
				
__Vectors
                DCD     __initial_sp            
                DCD     Reset_Handler            
__Vectors_End


__Vectors_Size  EQU  __Vectors_End - __Vectors

; *********   Reset handler

				AREA	|.text| , CODE,	READONLY
				
				EXPORT  Reset_Handler			[WEAK]
				IMPORT	_main
					
Reset_Handler 	PROC
				
				B _main
                ENDP
				
				ALIGN
				
				END