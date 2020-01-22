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
	hex_format db "%X", 0
	format db "%x %d", 0
	new_line_format db 13, 10, 0	
	a dd ?
	k dd ?
	m dd 11110000000000000000000000000000b
	
.CODE 
; В ЕАХ записывает количество незначащих битов
len proc
	MOV EAX, [ESP + 4]
	MOV ECX, 1
	XOR EBP, EBP
	j1:
		XOR ECX, ECX
		RCL EAX, 1
		ADC ECX, 0
		XOR ECX, 0
		INC EBP
	LOOP j1
	SUB EBP, 1
	RET 4
len endp

; Вводится чисто а и k. Циклически сдвинуть а на k влево
shift proc
	MOV EBX, [ESP + 8]
	MOV EAX, [ESP + 4]	
	XOR EDX, EDX
	
	MOV EDX, EAX
	
	ROR EDX, 4
	AND EDX, m
	ROL EDX, 4
	XOR EAX, EDX;
	ROR EDX, 4
	XOR ECX, ECX
	MOV ECX, EBX
	SUB ECX, 1
	j3:
		ROR EDX, 4
	LOOP j3
	;RCL EAX, 4
	ADD EAX, EDX
	XOR EDX, EDX

	ROR EAX, 4
		
	RET 8
shift endp


START:
	XOR ECX, ECX
	XOR EBX, EBX
	
	PUSH OFFSET k
	PUSH OFFSET a
	PUSH OFFSET format
	CALL crt_scanf
	ADD ESP, 4 * 3
	MOV EAX, a
	
	PUSH EAX
	CALL len
	
	XOR EDX, EDX
	
	MOV AX, BP
	MOV BX, 4
	DIV BX
	XOR EBX, EBX
	CWDE
	MOV BX, AX
	
	
	MOV EAX, a
	
	INC k
	t:
		MOV ECX, k
		PUSH EBX
		PUSH EAX
		CALL shift
		DEC k
		MOV ECX, k
	LOOP t
	
	
	PUSH EAX
	PUSH OFFSET hex_format
	CALL crt_printf
	ADD ESP, 8

	CALL crt__getch ; Задержка ввода с клавиатуры
	PUSH 0
	CALL ExitProcess ; Выход из программы
END START 