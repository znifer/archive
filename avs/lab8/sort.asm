.386
.model flat, stdcall
option casemap :none

.code
; Инициализирующая функция
DLLMain proc hlnstDLL:DWORD, reason:DWORD, unused:DWORD
  mov EAX, 1 
  ret
DLLMain endp

LibMain proc hlnstDLL:DWORD, reason:DWORD, unused:DWORD
  mov EAX, 1 
  ret
LibMain endp

copy_int_arr proc
	push ebp
	mov ebp, esp	
	add ebp, 4
	push esi
	push edi
	push ecx
	push eax
	push edx
	mov esi, [ebp+4+12]
	mov eax, [ebp+4]
	mov ecx, 4
	mul ecx
	add esi, eax
	mov edi, [ebp+4+8]
	mov ecx, [ebp+4+4]
	sub ecx, [ebp+4]
	inc ecx
	cld
	rep movsd
	pop edx
	pop eax
	pop ecx
	pop edi
	pop esi
	pop ebp
	ret 16
copy_int_arr endp
	
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