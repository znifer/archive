.486 
.MODEL FLAT, STDCALL 
OPTION CASEMAP: NONE 
INCLUDE C:\MASM32\INCLUDE\WINDOWS.INC 
INCLUDE C:\MASM32\INCLUDE\KERNEL32.INC 
INCLUDE C:\MASM32\INCLUDE\USER32.INC 
INCLUDE C:\masm32\include\msvcrt.inc
INCLUDELIB C:\MASM32\LIB\USER32.LIB 
INCLUDELIB C:\MASM32\LIB\KERNEL32.LIB 
INCLUDELIB C:\masm32\lib\msvcrt.lib
.DATA	
	number_format db "%d: ", 0
	number dd 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d, 0d,0d, 0d, 0d, 0d, 0d,0d, 0d, 0d, 0d, 0d,0d, 0d, 0d, 0d, 0d,0d, 0d, 0d, 0d, 0d,0d, 0d, 0d, 0d, 0d,0d, 0d, 1d, 0d, 1d
.CODE 
;40 байт умножение без знака
multiplication proc
    PUSH EAX
    PUSH EBX
    PUSH ECX
    PUSH EDX
	XOR EDX, EDX
	MOV ECX, [esp + 4 * 5]
	j1:
		PUSH ECX
		MOV ECX, 0
		CLC; сброс флага переноса
		j2:
			
		jl j2
		POP ECX
	LOOP j1
	POP edx
    POP ecx
    POP ebx
    POP eax
    RET 8
multiplication endp

START:
	PUSH OFFSET number
	PUSH 2
	CALL multiplication
	
	PUSH 0
	CALL ExitProcess
END START 