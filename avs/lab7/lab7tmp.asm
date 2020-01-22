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
	
.CODE 

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
	MOV ECX, n

	MOV EBX, shift
	comparing_loop:
		;Получаем очередное слово		
		PUSH EBX
		CALL get_next_word
		ADD EBX, len
		INC EBX
		MOV shift, EBX
		
		PUSH offset cmp_word
		PUSH offset tmp_str
		call compare
		
		CMP EAX, 1
		JE skip_word
		
		call is_one_error
		;CMP EAX, 1
		;JL skip_word
		
		;XOR EAX, EAX
		;CALL rewrite
		
		MOV ECX, n
		SUB ECX, shift

		skip_word:
	LOOP comparing_loop	
check endp

;EAX = 0, если более одной ошибки в слове
is_one_error proc
	PUSH ECX
	PUSH EBX
	PUSH EAX
	XOR ECX, ECX
	MOV ESI, offset cmp_word
	MOV EDI, offset tmp_str
	MOV ECX, len
	INC ECX
	
	XOR EAX, EAX; Счетчик количества ошибок
	;zf, jz, jnz
	
	REPE CMPSB
	INC EAX
	JNE ch1
		
	ch2:
	REPE CMPSB
	JNE no_edit
	JMP edit
	
	ch1:
	CMP ECX, 0
	JE edit
	JMP ch2
	
	edit:
	;MOV EDI, ESI
	MOV EAX, 2
	
	
	no_edit:
	POP EAX
	POP EBX
	POP ECX
is_one_error endp

rewrite proc
	;PUSH ECX
	
	;POP ECX
rewrite endp

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

START:
	PUSH offset inp_str
	CALL crt_gets
	ADD ESP, 4
	
	PUSH offset inp_str
	CALL get_len
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
	
	call check
		
	call crt__getch	
	push NULL 
	call ExitProcess 
END START 