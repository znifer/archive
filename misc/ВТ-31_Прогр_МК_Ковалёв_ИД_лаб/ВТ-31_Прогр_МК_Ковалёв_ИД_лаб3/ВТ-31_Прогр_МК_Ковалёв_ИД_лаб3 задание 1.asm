org 0h
jmp main

org 00Bh				; Вектор прерываний таймера 0
	mov A, #0
	movc A, @A+DPTR		; Смещаемся по таблице
	mov P1, A			; Выводим значение таблицы
	inc DPL				; Увеличиваем младшую часть DPTR, чтобы не выходить за границы таблицы (Например, с 0100h до 01FFh)		
	clr TF0				; Сбрасываем флаг прерывания
reti

org 30h
main:
	mov TMOD, #02h 		; Таймер 0, режим 3, автоматическая перезагрузка
 	setb EA				; Включаем глобальные прерывания
	setb ET0			; и прерывания от таймера 0
	mov TH0, #00FFh		; Настраиваем частоту вызова прерываний по таймеру
	mov TL0, #00FFh
    mov DPTR, #0100h	; Начальный адрес таблицы в DPTR
    clr P0.7			; Включаем ЦАП
	setb TR0			; Включаем таймер
	wait:
	jmp wait

org 0100h
db 0x80, 0x92, 0xa5, 0xb6, 0xc7, 0xd6, 0xe3, 0xee, 0xf6, 0xfc, 0xff, 0xff, 0xfd, 0xf8, 0xf0, 0xe6, 0xd9, 0xcb, 0xbb, 0xa9, 0x97, 0x84, 0x71, 0x5f, 0x4d, 0x3c, 0x2d, 0x1f, 0x14, 0xb, 0x4, 0x1, 0x0, 0x1, 0x6, 0xd, 0x17, 0x23, 0x30, 0x40, 0x51, 0x63, 0x76, 0x89, 0x9c, 0xae, 0xbf, 0xcf, 0xdc, 0xe8, 0xf2, 0xf9, 0xfe, 0xff, 0xfe, 0xfb, 0xf4, 0xeb, 0xe0, 0xd2, 0xc3, 0xb2, 0xa0, 0x8e, 0x7b, 0x68, 0x56, 0x44, 0x34, 0x26, 0x19, 0xf, 0x7, 0x2, 0x0, 0x0, 0x3, 0x9, 0x11, 0x1c, 0x29, 0x38, 0x49, 0x5a, 0x6d, 0x80, 0x92, 0xa5, 0xb6, 0xc7, 0xd6, 0xe3, 0xee, 0xf6, 0xfc, 0xff, 0xff, 0xfd, 0xf8, 0xf0, 0xe6, 0xd9, 0xcb, 0xbb, 0xa9, 0x97, 0x84, 0x71, 0x5f, 0x4d, 0x3c, 0x2d, 0x1f, 0x14, 0xb, 0x4, 0x1, 0x0, 0x1, 0x6, 0xd, 0x17, 0x23, 0x30, 0x40, 0x51, 0x63, 0x76, 0x89, 0x9c, 0xae, 0xbf, 0xcf, 0xdc, 0xe8, 0xf2, 0xf9, 0xfe, 0xff, 0xfe, 0xfb, 0xf4, 0xeb, 0xe0, 0xd2, 0xc3, 0xb2, 0xa0, 0x8e, 0x7b, 0x68, 0x56, 0x44, 0x34, 0x26, 0x19, 0xf, 0x7, 0x2, 0x0, 0x0, 0x3, 0x9, 0x11, 0x1c, 0x29, 0x38, 0x49, 0x5a, 0x6d, 0x7f, 0x92, 0xa5, 0xb6, 0xc7, 0xd6, 0xe3, 0xee, 0xf6, 0xfc, 0xff, 0xff, 0xfd, 0xf8, 0xf0, 0xe6, 0xd9, 0xcb, 0xbb, 0xa9, 0x97, 0x84, 0x71, 0x5f, 0x4d, 0x3c, 0x2d, 0x1f, 0x14, 0xb, 0x4, 0x1, 0x0, 0x1, 0x6, 0xd, 0x17, 0x23, 0x30, 0x40, 0x51, 0x63, 0x76, 0x89, 0x9c, 0xae, 0xbf, 0xcf, 0xdc, 0xe8, 0xf2, 0xf9, 0xfe, 0xff, 0xfe, 0xfb, 0xf4, 0xeb, 0xe0, 0xd2, 0xc3, 0xb2, 0xa0, 0x8e, 0x7b, 0x68, 0x56, 0x44, 0x34, 0x26, 0x19, 0xf, 0x7, 0x2, 0x0, 0x0, 0x3, 0x9, 0x11, 0x1c, 0x29, 0x38, 0x49, 0x5a, 0x6d, 0x7f
org 0200h
db 0x0, 0x6, 0xc, 0x12, 0x18, 0x1f, 0x25, 0x2b, 0x31, 0x37, 0x3e, 0x44, 0x4a, 0x50, 0x57, 0x5d, 0x63, 0x69, 0x6f, 0x76, 0x7c, 0x82, 0x88, 0x8f, 0x95, 0x9b, 0xa1, 0xa7, 0xae, 0xb4, 0xba, 0xc0, 0xc7, 0xcd, 0xd3, 0xd9, 0xdf, 0xe6, 0xec, 0xf2, 0xf8, 0xff, 0x0, 0x6, 0xc, 0x12, 0x18, 0x1f, 0x25, 0x2b, 0x31, 0x37, 0x3e, 0x44, 0x4a, 0x50, 0x57, 0x5d, 0x63, 0x69, 0x6f, 0x76, 0x7c, 0x82, 0x88, 0x8f, 0x95, 0x9b, 0xa1, 0xa7, 0xae, 0xb4, 0xba, 0xc0, 0xc7, 0xcd, 0xd3, 0xd9, 0xdf, 0xe6, 0xec, 0xf2, 0xf8, 0xff, 0x0, 0x6, 0xc, 0x12, 0x18, 0x1f, 0x25, 0x2b, 0x31, 0x37, 0x3e, 0x44, 0x4a, 0x50, 0x57, 0x5d, 0x63, 0x69, 0x6f, 0x76, 0x7c, 0x82, 0x88, 0x8f, 0x95, 0x9b, 0xa1, 0xa7, 0xae, 0xb4, 0xba, 0xc0, 0xc7, 0xcd, 0xd3, 0xd9, 0xdf, 0xe6, 0xec, 0xf2, 0xf8, 0xff, 0x0, 0x6, 0xc, 0x12, 0x18, 0x1f, 0x25, 0x2b, 0x31, 0x37, 0x3e, 0x44, 0x4a, 0x50, 0x57, 0x5d, 0x63, 0x69, 0x6f, 0x76, 0x7c, 0x82, 0x88, 0x8f, 0x95, 0x9b, 0xa1, 0xa7, 0xae, 0xb4, 0xba, 0xc0, 0xc7, 0xcd, 0xd3, 0xd9, 0xdf, 0xe6, 0xec, 0xf2, 0xf8, 0xff, 0x0, 0x6, 0xc, 0x12, 0x18, 0x1f, 0x25, 0x2b, 0x31, 0x37, 0x3e, 0x44, 0x4a, 0x50, 0x57, 0x5d, 0x63, 0x69, 0x6f, 0x76, 0x7c, 0x82, 0x88, 0x8f, 0x95, 0x9b, 0xa1, 0xa7, 0xae, 0xb4, 0xba, 0xc0, 0xc7, 0xcd, 0xd3, 0xd9, 0xdf, 0xe6, 0xec, 0xf2, 0xf8, 0xff, 0x0, 0x6, 0xc, 0x12, 0x18, 0x1f, 0x25, 0x2b, 0x31, 0x37, 0x3e, 0x44, 0x4a, 0x50, 0x57, 0x5d, 0x63, 0x69, 0x6f, 0x76, 0x7c, 0x82, 0x88, 0x8f, 0x95, 0x9b, 0xa1, 0xa7, 0xae, 0xb4, 0xba, 0xc0, 0xc7, 0xcd, 0xd3, 0xd9, 0xdf, 0xe6, 0xec, 0xf2, 0xf8, 0xff
org 0300h
db 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
