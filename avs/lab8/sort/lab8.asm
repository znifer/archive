.386
.model flat, stdcall
option casemap :none
.code
DLLMain proc hlnstDLL:DWORD, reason:DWORD, unused:DWORD
  mov EAX, 1 
  ret
DLLMain endp

LibMain proc hlnstDLL:DWORD, reason:DWORD, unused:DWORD
  mov EAX, 1 
  ret
LibMain endp

swap proc
	push eax
	push ebx 
	push ecx 
	push edx 
	push esi 
	push ebp 
	mov ebp, [esp + 36]
	mov esi, [esp + 32]
	mov ebx, [esp + 28]
	mov eax, [ebp + 4 * esi]
	mov edx, [ebp + 4 * ebx]
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
			mov eax, [ecx + edx * 4]
			mov ebx, [ecx + ebp * 4]
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

copy proc
	push ebp
	mov ebp, esp	
	add ebp, 4
	push esi
	push edi
	push ecx
	push eax
	push edx
	mov esi, [ebp + 4 + 12]
	mov eax, [ebp + 4]
	mov ecx, 4
	mul ecx	
	add esi, eax
	mov edi, [ebp + 4 + 8]
	mov ecx, [ebp + 4 + 4]
	sub ecx, [ebp + 4] 
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
copy endp

sort_stdcall proc
	push ebp				; пролог
	mov ebp, esp			; сохранение адреса вершины стека в регистре ebp - пролог
	push [ebp + 8 + 12]		; *a
	push [ebp + 8 + 8]		; *res
	push [ebp + 8 + 4]		; fin
	push [ebp + 8]			; strt
	call copy
	mov eax, [ebp + 8 + 4]	
	sub eax, [ebp + 8]		
	inc eax					; eax = size
	push eax				; size
	push [ebp + 8 + 8]		; адрес массива res
	call sort				
	mov eax, [ebp + 8 + 8]	; возврат адреса массива res 
	leave					; эпилог
	ret 16
sort_stdcall endp

sort_cdecl proc
	push ebp				; пролог
	mov ebp, esp			; сохранение адреса вершины стека в регистре ebp - пролог	
	push [ebp + 8 + 12]		; *a
	push [ebp + 8 + 8]		; *res
	push [ebp + 8 + 4]		; end
	push [ebp + 8]			; start 
	call copy				
	mov eax, [ebp + 8 + 4]	
	sub eax, [ebp + 8]		
	inc eax					; eax = size
	push eax				; size
	push [ebp + 8 + 8]		; адрес массива res
	call sort				
	mov eax, [ebp + 8 + 8]	; возврат адреса массива res 
	leave					; эпилог
	ret
sort_cdecl endp

sort_fastcall proc
	push ebp				; пролог
	mov ebp, esp			; сохранение адреса вершины стека в регистре ebp - пролог
	push [ebp + 8 + 4]		; *a
	push [ebp + 8]			; *res
	push edx				; end
	push ecx				; start
	call copy				
	sub edx, ecx			; edx = size
	inc edx				
	push edx				; size
	push [ebp + 8]			; адрес массива res
	call sort	
	mov eax, [ebp + 8]		; возврат адреса массива res 
	leave					; эпилог
	ret 8
sort_fastcall endp

sort_stdcall_args proc strt:dword, fin:dword, res:dword, a:dword
	push a
	push res
	push fin
	push strt
	call copy			
	mov eax, fin		
	sub eax, strt		
	inc eax				; eax = size
	push eax			; size
	push res			; адрес массива res
	call sort	
	mov eax, res		; возврат адреса массива res 
	ret 16
sort_stdcall_args endp

sort_cdecl_args proc c strt:dword, fin:dword, res:dword, a:dword
	push a
	push res
	push fin
	push strt
	call copy	
	mov eax, fin		
	sub eax, strt		; eax = size
	inc eax				
	push eax			; size
	push res			; адрес массива res
	call sort	
	mov eax, res		; возврат адреса массива res 
	ret
sort_cdecl_args endp

end LibMain