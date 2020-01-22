.386                    ; Тип процессора
.model flat, stdcall    ; Модель памяти и стиль вызова подпрограмм
option casemap: none   	; Чувствительность к регистру
include C:\masm32\include\windows.inc
include C:\masm32\include\kernel32.inc
include C:\masm32\include\msvcrt.inc
include C:\masm32\include\user32.inc
includelib C:\masm32\lib\user32.lib
includelib C:\masm32\lib\kernel32.lib
includelib C:\masm32\lib\msvcrt.lib

.data
	a dd 10, 3, 4, -5, 7, -2, -1, 3, 5, -5
	res dd 10 dup(?)
	len dd 9
	strt dd 0d
	fin dd 9d
	
.code

swap proc
	push eax
	push ebx 
	push ecx 
	push edx 
	push esi 
	push ebp 
	mov ebp,[esp + 36]
	mov esi,[esp + 32]
	mov ebx,[esp + 28]
	mov eax,[ebp + 4 * esi]
	mov edx,[ebp + 4 * ebx]
	mov ecx,edx
	mov edx,eax
	mov eax,ecx
	mov [ebp + 4 * esi], eax
	mov [ebp + 4 * ebx], edx
	pop ebp
	pop esi 
	pop edx
	pop ecx
	pop ebx
	pop eax
	ret 12
swap endp


sort proc
	push eax
	push ebx 
	push ecx
	push edx 
	push esi
	push ebp
	mov ecx, [esp + 28]
	xor esi, esi
	xor edx, edx
	xor ebp, ebp
	mov esi, -1
	i_cycle:
		add esi, 1
		mov ebp, esi
		mov edx, esi
		j_cycle:
			add edx, 1
			mov eax,[ecx + edx * 4]
			mov ebx,[ecx + ebp * 4]
			cmp eax, ebx
			jnl not_if1
			mov ebp, edx
			not_if1:
			mov eax, [esp + 32]
			sub eax, 1
			cmp edx, eax
			jl j_cycle
		cmp ebp, esi
		je not_if2
		push ecx
		push esi
		push ebp
		call swap
		mov ebp, esi
		not_if2:
		mov eax, [esp+32]
		sub eax, 2
		cmp esi, eax
		jl i_cycle
	pop ebp
	pop esi 
	pop edx
	pop ecx
	pop ebx
	pop eax
	ret 8
sort endp

start:
	push len
	push offset a
	
	call sort
    push 0
	call ExitProcess ; выход из программы
end start