#include "define.h"

__asm void strcpy_and_reverse(const char *src, char *dst, long array_size){
	
	PUSH {r4}
	MOV r4, r0
	ADDS r0, r0, r2 
	SUBS r0, r0, #2

loop
	LDRB r3, [r0]
	STRB r3, [r1]
	CMP r0, r4
	BEQ end
	SUBS r0, r0, #1
	ADDS r1, r1, #1
	B loop
	
end
	POP {r4}
	BX lr
}	
	
		
	
		