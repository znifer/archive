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
	len dd 0
	n dd 0
	shift dd 0
	inp_str db 32 dup(?)
	cmp_word db 32 dup(?)
	tmp_str db 32 dup(?)
	num_format db "%d", 0
	str_format db "%s ", 0
	
.CODE 

;в ЕАХ запишет количество различных символов
is_one_error proc
	PUSH ECX
	PUSH EBX
	XOR ECX, ECX
	MOV ESI, offset cmp_word
	MOV EDI, offset tmp_str
	MOV ECX, len	
	XOR EAX, EAX; Счетчик количества ошибок	
	cmp_loop:
		REPE CMPSB
		JNE inc_errors
		JE def	
		inc_errors:
		INC EAX		
		def:
		INC ECX
	LOOP cmp_loop
	POP EBX
	POP ECX
	RET 4
is_one_error endp

get_len proc
	MOV EDI, [ESP + 4]
	MOV AL, 0
	MOV ECX, -1
	REPNE SCASB
	MOV ECX, EDI
	SUB ECX, [ESP + 4]
	RET 4
get_len endp

;С клавиатуры вводятся слово a и строка. Исправить в строке одиночные
;ошибки в словах a. Считать, что длины исходного слова и исправляемого
;равны.

check proc
	MOV EBX, shift
	MOV ECX, n
	comparing_loop:
		;Получаем очередное слово		
		PUSH EBX
		CALL get_next_word
		ADD EBX, len
		INC EBX
		MOV shift, EBX
		
		;Сравниваем очередное слово с исходным
		PUSH offset cmp_word
		PUSH offset tmp_str
		CALL compare
		CMP EAX, 1
		JE skip_word	;Пропускаем слово, если равны
		;Если слова не равны, проверяем количество ошибок
		XOR EAX, EAX
		PUSH EAX
		CALL is_one_error
		
		CMP EAX, 1
		JNE skip_word
		
		ADD EDX, 10000
		PUSH offset cmp_word
		PUSH offset str_format
		CALL crt_printf
		ADD ESP, 8
		jmp end_cycle
		
		
		skip_word:
		PUSH offset tmp_str
		PUSH offset str_format
		CALL crt_printf
		ADD ESP, 8
		
		end_cycle:
		MOV ECX, n
		SUB ECX, shift
		INC ECX
	LOOP comparing_loop	
check endp

;В ЕАХ запишет 1, если слова равны, иначе -1
compare proc
	PUSH ECX
	PUSH EBX
	PUSH ESI
	PUSH EDI
	
	MOV ECX, len
	MOV ESI, [ESP + 4 * 5]
	MOV EDI, [ESP + 4 * 6]
	REPE CMPSB

	JA j1
	JB j1
	JE j2 ; равны
	
	j1:
	MOV EAX, -1
	JMP compare_end
		
	j2:
	MOV EAX, 1
	JMP compare_end	
	
	compare_end:
	POP EDI
	POP ESI
	POP EBX
	POP ECX
	RET 8
compare endp

;EBX - количество пропущенных символов с начала строки
get_next_word proc
	PUSH ECX
	MOV ESI, offset inp_str
	ADD ESI, EBX; прибавляем количество символов, которые нужно пропустить
	MOV EDI, offset tmp_str
	
	MOV ECX, len; сколько символов скопировать
	REP MOVSB
	POP ECX
	RET 4
get_next_word endp

START:
	PUSH offset inp_str
	CALL crt_gets
	ADD ESP, 4
	
	PUSH offset inp_str
	CALL get_len
	DEC ECX
	MOV n, ECX
	
	PUSH offset cmp_word
	CALL crt_gets
	ADD ESP, 4
	
	PUSH offset cmp_word
	CALL get_len
	DEC ECX
	MOV len, ECX
	
	;XOR EAX, EAX
	;MOV AX, WORD PTR n
	;MOV BX, WORD PTR len
	;DIV BX
	
	CALL check
		
	CALL crt_getc
	push NULL 
	call ExitProcess 
END START 