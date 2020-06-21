org 0h
CLR SM0
SETB SM1; 2 режим, 8 бит, стоп/старт, четность
jmp start

start:
	; Поочередно выставляем на каждой ноге 0 и сканируем столбец
	; После каждой проверки возвращаем 1 
	CLR P0.0	
	CALL colScan0 ; вызываем опрос столбца 1
	SETB P0.0

	CLR P0.1	
	CALL colScan1 ; вызываем опрос столбца 2
	SETB P0.1

	CLR P0.2	
	CALL colScan2 ; вызываем опрос столбца 3
	SETB P0.2

	CLR P0.3
	CALL colScan3 ; вызываем опрос столбца 4
	SETB P0.3
	
	jmp start ; И повторяем
end

; Поочередно сравниваем значения на каждой ноге P1.
; Если где то 0 - уже будем знать, какой символ нажат.
colScan0:
	JNB P1.0, gotKey1
	JNB P1.1, gotKey2
	JNB P1.2, gotKey3
	JNB P1.3, gotKeyC
	JNB P1.4, gotKeyD
ret

colScan1:
	JNB P1.0, gotKey4
	JNB P1.1, gotKey5
	JNB P1.2, gotKey6
	JNB P1.3, gotKeyE
	JNB P1.4, gotKeyF
ret

colScan2:
	JNB P1.0, gotKey7
	JNB P1.1, gotKey8
	JNB P1.2, gotKey9
	JNB P1.3, gotKeyG
	JNB P1.4, gotKeyH
ret

colScan3:
	JNB P1.0, gotKeyA
	JNB P1.1, gotKey0
	JNB P1.2, gotKeyB
	JNB P1.3, gotKeyI
	JNB P1.4, gotKeyJ
ret
; В r0 помещаем ASCII-код
gotKey0:
	mov r0, #48
	call print
ret

; Выводим ASCII-код, который записан в r0
print:
	mov a, r0
	MOV C, P
	MOV ACC.7, C
	MOV SBUF, A
	JNB TI, $
	CLR TI
ret

gotKey1:
	mov r0, #49
	call print
ret

gotKey2:
	mov r0, #50
	call print
ret

gotKey3:
	mov r0, #51
	call print
ret

gotKey4:
	mov r0, #52
	call print
ret

gotKey5:
	mov r0, #53
	call print
ret

gotKey6:
	mov r0, #54
	call print
ret

gotKey7:
	mov r0, #55
	call print
ret

gotKey8:
	mov r0, #56
	call print
ret

gotKey9:
	mov r0, #57
	call print
ret

gotKeyA:
	mov r0, #65
	call print
ret

gotKeyB:
	mov r0, #66
	call print
ret

gotKeyC:
	mov r0, #67
	call print
ret

gotKeyD:
	mov r0, #68
	call print
ret

gotKeyE:
	mov r0, #69
	call print
ret

gotKeyF:
	mov r0, #70
	call print
ret

gotKeyG:
	mov r0, #71
	call print
ret

gotKeyH:
	mov r0, #72
	call print
ret

gotKeyI:
	mov r0, #73
	call print
ret

gotKeyJ:
	mov r0, #74
	call print
ret