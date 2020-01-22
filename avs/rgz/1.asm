.386
.model flat,stdcall
option casemap:none
include C:\masm32\include\windows.inc
include C:\masm32\include\user32.inc
include C:\masm32\include\kernel32.inc
include C:\masm32\include\gdi32.inc
INCLUDE C:\masm32\include\msvcrt.inc
includelib C:\masm32\lib\msvcrt.lib
includelib C:\masm32\lib\user32.lib 
includelib C:\masm32\lib\kernel32.lib 
includelib C:\masm32\lib\gdi32.lib
 
WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
.data?
hInstance dd ? 
CommandLine dd ?
.data
ClassName db "SimpleWinClas",0
AppName db "Kovalyov I. D.",0
maxX SDWORD ? 
maxY SDWORD ? 

sx SDWORD ? 		;������ ���� �� �
sy SDWORD ? 		;������ ���� �� �

;���������
c100  SDWORD 100
c1 	  SDWORD 1
c0	  SDWORD 0

;��������� ����������
temp  SDWORD ? 
t1 	  SDWORD ?
t2 	  SDWORD ?

;��������� ������
ballX 	SDWORD 300 	;x 
ballY	SDWORD 300	;y
ballR 	SDWORD 10 	;������ ����
ballDX 	SDWORD 5 	;�������� �� �
ballDY 	SDWORD 4	;�������� �� �
ballS 	SDWORD 2 	

;������ ������ �������������� � ������ ������ ����, ������� ������ ������ ������ ����������
circleR SDWORD 400
 
hdc 	SDWORD ?
memBit 	SDWORD ?
hBitmap SDWORD ?

; ��������� - �������
normX SDWORD ?
normY SDWORD ?
normX2 SDWORD ?
normY2 SDWORD ?
scalar SDWORD ?
len SDWORD ?

ps	PAINTSTRUCT <?>
.code 

;�������� ������
circle_check proc
	pushad
		;a[esp+52] - � ������ �������
		;b[esp+48] - � ������ �������
        ;r[esp+44] - ������ �������
		;x[esp+40] - ���������� ������ �� �
		;y[esp+36] - ���������� ������ �� �
		
		;x-a
		fild dword ptr [esp + 40] ; st(1) = x
		fild dword ptr [esp + 52] ; st(0) = a
		fsubp st(1), st(0)
		fmul st(0), st(0)
        ;y-b
        fild dword ptr [esp + 36] ; st(1) = y
        fild dword ptr [esp + 48] ; st(0) = b
		fsubp st(1), st(0)
		fmul st(0), st(0)
        faddp st(1), st(0)
        
		fild dword ptr [esp + 44] ; st(0) = r
		fiadd ballR				  ; ����������� ��������� ������ ������
		fmul st(0), st(0)
	popad
        db 0dbh, 0f0h+1
        jae check_eq
        check_neq:
            mov eax,0
            jmp check_end
        check_eq:
            mov eax,1
        check_end:
            FFREE st(0) 
            FFREE st(1) 
			FFREE st(2)
			FFREE st(3)
    ret 20
circle_check endp

start:
		invoke GetModuleHandle, NULL 
		mov	hInstance,eax ;���������� ���������� ����������
		;���� ���������� �������� ����� ������ ���� ��������� � �� �������� ������������. 
		;���������� hInstance ���� ����� ��������� ��������, ���������� � ��������� ���������.
		
		;HINSTANCE hPrevInstance � ���������� ����������� ���������� ����������.
		;���� ���������� ������� �� ������ ������ Windows - ������ �����, ��� �� ������� �� ����������.
		;HINSTANCE hPrevInstance=NULL � ���������
		invoke GetCommandLine ;get
		mov	CommandLine,eax ;��������� �� ������ ��������� ������, ��������� ��� ������� ���������.
		;int nCmdShow � ��� �������� �������� �������� ��� ���� (��������, ��������� ��� �����������)
		;int nCmdShow=SW_SHOWDEFAULT 
		invoke WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT 
		invoke ExitProcess, eax

WinMain proc hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:DWORD
		LOCAL wc:WNDCLASSEX ;SS:0018FF68  ��������� WNDCLASSEX �������� ���������� � ������ ���a
		LOCAL msg:MSG ;SS:0018FF4C //��������� ���������
		LOCAL hwnd:HWND ;SS:0018FF78 ���������� - ���������� ����� ���������� ���� ���������
	
		mov wc.cbSize, SIZEOF WNDCLASSEX ;������������� ������ ���� ���������, � ������
		mov wc.style, CS_HREDRAW or CS_VREDRAW ;������������� �����(�) ������. ���� ���� ��������� ����� ���� ����� ����������� ������ ������
		mov wc.lpfnWndProc,OFFSET   WndProc ;��������� �� ������� ���������.
		mov wc.cbClsExtra,NULL ;������������� ����� �������������� ����, ������� ����������� ����� �� ���������� ������ ����
		mov wc.cbWndExtra,NULL ;������������� ����� �������������� ������, ������� ����������� ����� �� ����������� ����
		push hInstance ;���������� ����������, ������� �������� ������� ��������� ��� ������.
		pop wc.hInstance
		mov wc.hbrBackground, COLOR_WINDOW+1;���������� ����� ���� ������.
		mov wc.lpszMenuName ,NULL ;��������� �� ���������� ������ � �������� ����� ������ ('\0')
		mov wc.lpszClassName, OFFSET ClassName ;��������� �� ���������� ������ � ����� � ����� ���  ����
	
		invoke LoadIcon,hInst,500
		mov wc.hIcon, eax ;���������� ������ ������
		
		mov wc.hIconSm,eax ;���������� ���������� ������, ������� ������ � ������� ����
		invoke LoadCursor,NULL,IDC_ARROW
		mov wc.hCursor,eax ;���������� ������� ������
		invoke RegisterClassEx,addr wc ; ������������ ����� ���� ��� ������������ �������������
		;CreateWindowEx ������� �������������, ������������� ��� �������� ���� � ����������� ������
		
		;DWORD dwExStyle,      // ���������� ����� ����
		;LPCTSTR lpClassName,  // ��������� �� ������������������ ��� ������
		;LPCTSTR lpWindowName, // ��������� �� ��� ����
		;DWORD dwStyle,        // ����� ����
		;int x,                // �������������� ������� ����
		;int y,                // ������������ ������� ����
		;int nWidth,           // ������ ����
		;int nHeight,          // ������ ����
		;HWND hWndParent,      // ���������� ������������� ��� ���� ���������
		;HMENU hMenu,          // ���������� ���� ��� ID ��������� ����
		;HINSTANCE hInstance,  // ���������� ���������� ���������� ���������
		;LPVOID lpParam        // ��������� �� ������ �������� ����
		
		;���� ������� ����������� �������, ������������ �������� - ���������� ���������� ����.
		INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,\
			13303808,CW_USEDEFAULT,\
			CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
			hInst,NULL
		mov hwnd,eax ;���������� ���������� ����.
		invoke LoadMenu,hInst,600 ;���p����� ������������� p���p� ����
		invoke SetMenu,hwnd,eax ;������������� � ��p�p��������� ���� ���� ��� ����, ��p��������� ��p����p�� Menu
	
		invoke ShowWindow,hwnd,SW_SHOWNORMAL ;hwnd-������������p ���� 
		;����p����� ��� �p���� ���� ��p����, ��������� ��p����p�� CmdShow
		invoke UpdateWindow,hwnd  ;��������� ������� ������� ��������� ���� hwnd -���������� ����
		.WHILE TRUE ;��������� ���� ��������� ���������
		
				;ADDR msg ��������� �� ��������� ���������, 
				;� ������� GetMessage ������ ���������.
				;2 �������� -��������� ����, �� �������� GetMessage ������ ��������� 
				;(NULL ��������, ��� GetMessage ��������� ��������� �� ���� ����, ������������� ������
				;3 �������� UINT wMsgFilterMin � ���������� ������������� ���������, ������� ������ GetMessage
				;4 �������� UINT wMsgFilterMax � ���������� ������������� ���������, ������� ������ GetMessage 
				;(���� � ��������� ���������� wMsgFilterMin � wMsgFilterMax �������� 0, ������� ����� ��������� ��� ���������)
				invoke GetMessage,ADDR msg,NULL,0,0
				;� eax ��������� -���������� ���������
				.BREAK .IF (!eax)
				invoke TranslateMessage, ADDR msg ;��������� use ����������
				invoke DispatchMessage, ADDR msg ;������� ���������� windows
		.ENDW
		mov eax,msg.wParam ;���������� �������������� ���������� � ���������
		ret
WinMain endp
;		HWND hwnd,���������� ������� ���������, ������� �������� ���������
;		UINT uMsg,���������� ���������.
;		WPARAM wParam,���������� �������������� ���������� � ���������
;		LPARAM lParam ���������� �������������� ���������� � ���������
WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
		;##################################close window
		.if uMsg==WM_DESTROY ;���������� ����� ���������� ���������� ����
		;������� DeleteObject ������� ���������� ����, �����, �����, �������� ��������, ������ ��� �������,
		;���������� ��� ��������� �������, ��������� � ��������
			invoke DeleteObject,memBit;���������� ������������ �������
		;������� PostQuitMessage ��������� �������, ��� ����� ������ ������ �� ��, ����� ��������� ���� ������
		;�������� ���������� ��� ���������� ���������� ���������.
			invoke PostQuitMessage, NULL
		;##################################create window
		.elseif uMsg==WM_CREATE ;��������� �����, ����� ��������� �����������, ������� ����� ������� CreateWindowEx ,������ ���� ������� ����
			;set timer 
			fild c1
			fild c100
			fdiv
			fst temp
			;HWND hWnd, ���������� ����, ������� ������� � ��������
			;UINT_PTR nIDEvent, ��������� ������������� ������� �������� �� ����
			;UINT uElapse,��������� �������� ������� �������, � �������������.
			;TIMERPROC lpTimerFun ��������� �� �������, ������� ����������, ����� �������� ������� ������� ��������
			invoke SetTimer,hWnd,1,c1,0
			
			
			
			; get max size window 
			invoke GetSystemMetrics, SM_CXSCREEN
			mov maxX, eax
			invoke GetSystemMetrics,SM_CYSCREEN;������ � ������ ������ � ��������
			mov maxY, eax
	
			; ��������� ��������� 
			;��������� ���������� ����������� ��������� ����������
			invoke GetDC, hWnd ;hWnd ���������� ����
			mov hdc, eax
			;�������� ����� � ������ 
			;c������ �������� ���������� � ������ 
			invoke CreateCompatibleDC, hdc 
			mov memBit, eax
			; CreateCompatibleBitmap  ������� �������� �������
			;HDC hdc,        // ���������� DC
			;int nWidth,     // ������ �������, � ��������
			;int nHeight     // ������ �������, � ��������
			invoke CreateCompatibleBitmap, hdc, maxX, maxY 
			mov hBitmap, eax
			;���� ������� ����������� �������, ������������ �������� - ���������� 
			;������������ ��������� ������� (���������-��������� �������� �������� (DDB)
		
			
			;SelectObject �������� ������ � �������� �������� ���������� (DC). 
			;����� ������ �������� ���������� ������ ���� �� ������ ���
			invoke SelectObject, memBit, hBitmap
			
			; ########################################### ���������
			.elseif uMsg==WM_PAINT ; ������� ��� ������ ���������� ������ ������ �� ������������ ����� ���� ����������
				; ��������� �������
				invoke PatBlt, memBit, 0, 0, maxX, maxY, WHITENESS
				;BOOL PatBlt(
				;HDC hdc,      // ���������� ��������� ���������� (DC)
				;int nXLeft,   // x-���������� �������� ������ ���� ��������������
				;int nYLeft,   // y-���������� �������� ������ ���� ��������������
				;int nWidth,   // ������ ��������������
				;int nHeight,  // ������ ��������������
				;DWORD dwRop   // ��� ��������� ��������
				invoke GetStockObject, c1;��������� ���������� ������ �� ���������������� (�����������) ������, ������, ������� ��� ������
				invoke SelectObject, memBit, eax
				;��������� �������
				fld sy
				fld circleR
				fadd
				fstp temp
				push temp
				
				fld sx
				fld circleR
				fadd
				fstp temp
				push temp
				
				fld sy
				fld circleR
				fsub
				fstp temp
				push temp
				
				fld sx
				fld circleR
				fsub
				fstp temp
				push temp
				
				push memBit
				call Ellipse
				
				; ��������� ������
				fld ballY
				fld ballR
				fadd
				fstp temp
				push temp
				
				fld ballX
				fld ballR
				fadd
				fstp temp
				push temp
				
				fld ballY
				fld ballR
				fsub
				fstp temp
				push temp
				
				fld ballX
				fld ballR
				fsub
				fstp temp
				push temp
				
				push memBit
				call Ellipse
				
				mov temp, 0
				
				;��������� �� ������ � ����
				;HWND hwnd,            // ���������� ����
				;LPPAINTSTRUCT lpPaint // ���������� �� �����������
				invoke BeginPaint, hWnd, offset ps
				mov hdc, eax
				
				;BOOL BitBlt(
				;HDC hdcDest, // ���������� �������� DC
				;int nXDest,  // x-�����. ������ �������� ���� �������� ��������������
				;int nYDest,  // y-�����. ������ �������� ���� �������� ��������������
				;int nWidth,  // ������ �������� ��������������
				;int nHeight, // ������ �������� ��������������
				;HDC hdcSrc,  // ���������� ��������� DC
				;int nXSrc,   // x-�����. ������ �������� ���� ��������� ��������������
				;int nYSrc,   // y-�����. ������ �������� ���� ��������� ��������������
				;DWORD dwRop  // ��� ��������� ��������
				invoke BitBlt, hdc, 0, 0, sx, sy, memBit, 0, 0, SRCCOPY
				invoke EndPaint, hWnd, offset ps ;�������� ����� ����������� � �������� ����
				
				
			;��������� ������� ���� 
			.elseif uMsg==WM_SIZE ;���������� ���� ����� ����, ��� ��� ������ ���������
				xor eax, eax
				mov ax, word ptr lParam
				mov sx, eax
				mov eax, eax
				mov eax, lParam
				shr eax, 16
				mov sy, eax
								
			;=========================================== ������������ ������� ================================
			.elseif uMsg==WM_TIMER
			;WM_TIMER �������� �����������������
			
			;=========================================== �������� �� �������� � �������� =====================
			xor eax,eax
			push sx
			push sy
			push circleR
			push ballX 
			push ballY 
			call circle_check
			.IF(eax == 1)
				fild ballX
				fisub sx ; (ballX-sx)
				; �������, ���������� X
				fstp normX

				fild ballY
				fisub sy ; (ballY-sy)
				; �������, ���������� Y
				fstp normY

				fld normX
				fmul normX
				fstp normX2 ; � ��������

				fld normY
				fmul normY
				fstp normY2

				fld normY2
				fadd normX2
				fsqrt
				; st(0) �������� ������ �������
				fstp len

				fld normX
				fdiv len
				fst normX ; normX - ������������

				fld normY
				fdiv len
				fst normY ; normY - ������������

				fild ballDX
				fmul normX
				fild ballDY
				fmul normY
				; ���� - ballDY * normY, ballDX * normX
				faddp st(1), st(0)
				
				mov temp, 2
				fimul temp

				fstp scalar ; �������� ��������� ������������ (���������� �� 2)

				fld normX
				fmul scalar
				; st(0) = normX * scalar
				fisubr ballDX ; st(0) = ballDX - st(0)
				frndint
				fistp ballDX

				fld normY
				fmul scalar
				; st(0) = normY * scalar
				fisubr ballDY ; st(0) = ballDY - st(0)
				frndint
				fistp ballDY
				;fild ballDX
				;FCHS
				;fistp ballDX		
				;fild ballDY
				;FCHS
				;fistp ballDY
			.ENDIF	

			;================================= �������� �� �������� � �������� =================================
			mov eax,ballX
			.IF(c0 >= eax || sx <= eax )
				fild ballDX
				FCHS
				fistp ballDX
			.ENDIF
			mov eax,ballY
			.IF(c0 >= eax || sy <= eax )
				fild ballDY
				FCHS
				fistp ballDY
			.ENDIF			
			
			;================================= �������� ������ ================================================
			; ���������� dx
			fild ballX
			fild ballDX
			fild ballS
			fmulp st(1),st
			faddp st(1),st
			FRNDINT
			fistp ballX
			; ���������� dy
			fild ballY
			fild ballDY
			fild ballS
			fmulp st(1),st
			faddp st(1),st
			FRNDINT
			fistp ballY
		
			invoke InvalidateRect, hWnd, 0, 0  ;��������� ������������� ��� ����������� ����
			;HWND hWnd,		// ��������� �� ����
			;CONST RECT *lpRect,	// ������������� �����������
			;BOOL bErase		// ����� �����������

			.else
				invoke DefWindowProc, hWnd, uMsg, wParam, lParam 
				;������� DefWindowProc ���������� ������� ���������� �� ���������,
				;����� ���������� ��������� �� ��������� ������ ��������� ����, ������� ���������� �� ������������
				ret
		.endif
	xor eax , eax
	ret
WndProc endp
end start	