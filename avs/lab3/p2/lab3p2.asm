.386 
.MODEL FLAT, STDCALL 
OPTION CASEMAP: NONE 
INCLUDE C:\MASM32\INCLUDE\WINDOWS.INC 
INCLUDE C:\MASM32\INCLUDE\KERNEL32.INC 
INCLUDE C:\MASM32\INCLUDE\USER32.INC 
INCLUDELIB C:\MASM32\LIB\USER32.LIB 
INCLUDELIB C:\MASM32\LIB\KERNEL32.LIB 
.DATA	
a db 015h, 03Eh, 0F9h, 0A0h, 076h, 033h, 02Fh, 0D5h, 0BBh, 0BBh, 0E6h, 035h, 0C2h, 002h, 03Eh, 08Eh, 0E8h, 0EAh, 007h, 014h, 08Fh 
b db 06Eh, 0E6h, 041h, 04Dh, 061h, 0A9h, 098h, 0F0h, 0CBh, 062h, 083h, 0EDh, 078h, 055h, 017h, 03Eh, 020h, 09Ah, 032h, 042h, 047h 

res db 22 dup(?) 
.CODE 
START: 
	MOV EAX, DWORD PTR [a+0]
	ADC EAX, DWORD PTR [b+0]  
	MOV DWORD PTR [res+0], EAX 
	
	MOV EAX, DWORD PTR [a+4]
	ADC EAX, DWORD PTR [b+4] ; 
	MOV DWORD PTR [res+4], EAX 
		
	MOV EAX, DWORD PTR [a+8]
	ADC EAX, DWORD PTR [b+8] ; 
	MOV DWORD PTR [res+8], EAX 

	MOV EAX, DWORD PTR [a+12]
	ADC EAX, DWORD PTR [b+12] ; 
	MOV DWORD PTR [res+12], EAX 
	
	MOV EAX, DWORD PTR [a+16]
	ADC EAX, DWORD PTR [b+16] ; 
	MOV DWORD PTR [res+16], EAX 
	
	MOV EAX, DWORD PTR [a+20]
	ADC EAX, DWORD PTR [b+20] ; 
	MOV DWORD PTR [res+20], EAX 
	
	MOV AL, a[21]
	ADC AL, b[16]
	MOV res[16], al
	
	ADC CL, DL
	MOV res[17], CL

push NULL 
call ExitProcess 
END START 