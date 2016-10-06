bits 32

%define CS_VREDRAW 1
%define CS_HREDRAW 2
%define CS_DBLCLKS 8

%define COLOR_WINDOW  5

%define WM_DESTROY  2

%define IDI_APPLICATION 32512
%define IDC_ARROW       32512

%define CW_USEDEFAULT   0x80000000

%define WS_OVERLAPPED   0x000000
%define WS_CAPTION      0xc00000
%define WS_SYSMENU      0x080000
%define WS_THICKFRAME   0x040000
%define WS_MINIMIZEBOX  0x020000
%define WS_MAXIMIZEBOX  0x010000
%define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

%define MB_OK 0
%define MB_ICONERROR 0x10

struc WNDCLASS
  .style:         resd  1
  .lpWndProc:     resd  1
  .cbClsExtra:    resd  1
  .cbWndExtra:    resd  1
  .hInstance:     resd  1
  .hIcon:         resd  1
  .hCursor:       resd  1
  .hbrBackground: resd  1
  .lpszMenuName:  resd  1
  .lpszClassName: resd  1
endstruc

struc MSG
  .hWnd:    resd  1
  .message: resd  1
  .wParam:  resd  1
  .lParam:  resd  1
  .time:    resd  1
  .pt:      resd  2
endstruc

section .data

winapp_class:
  db  "MyWinAppClass",0

winapp_title:
  db  "My Windows App",0

msg_caption:
  db  "Error",0

msg_text:
  db  "Error creating main window.",0

wc:
  istruc WNDCLASS
    at WNDCLASS.style,          dd  (CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS)
    at WNDCLASS.hbrBackground,  dd  (COLOR_WINDOW+1)
  iend

msg:
  istruc MSG
  iend

section .bss

hWnd:
  resd  1

section .text

extern __imp__LoadIconA@8
extern __imp__LoadCursorA@8
extern __imp__RegisterClassA@4
extern __imp__CreateWindowExA@48
extern __imp__MessageBoxA@16
extern __imp__UpdateWindow@4
extern __imp__ShowWindow@8
extern __imp__GetMessageA@16
extern __imp__TranslateMessage@4
extern __imp__DispatchMessageA@4
extern __imp__DefWindowProcA@16
extern __imp__PostQuitMessage@4

global _WindowMessagesHandler@16
%define arg_hWnd    ebp+8
%define arg_uMsg    ebp+12
%define arg_wParam  ebp+16
%define arg_lParam  ebp+20
_WindowMessagesHandler@16:
  push  ebp
  mov   ebp,esp  

  cmp   dword [arg_uMsg],WM_DESTROY
  jz    Handle_Destroy

  push  dword [arg_lParam]
  push  dword [arg_wParam]
  push  dword [arg_uMsg]
  push  dword [arg_hWnd]
  call  dword [__imp__DefWindowProcA@16]
  jmp   HandlerExit

Handle_Destroy:
  push  dword 0
  call  dword [__imp__PostQuitMessage@4]
  xor   eax,eax

HandlerExit:
  pop   ebp
  ret   16

%define arg_hInst       ebp+8
%define arg_hPrev       ebp+12
%define arg_lpszCmdLine ebp+16
%define arg_nCmdShow    ebp+20
global _WinMain@16
_WinMain@16:
  push  ebp
  mov   ebp,esp

  ;-----------------
  ; Registra a classe de janela.
  ;-----------------
  mov   eax,[arg_hInst]
  mov   [wc+WNDCLASS.hInstance],eax

  push  dword IDI_APPLICATION
  push  dword 0
  call  dword [__imp__LoadIconA@8]
  mov   [wc+WNDCLASS.hIcon],eax

  push  dword IDC_ARROW
  push  0
  call  dword [__imp__LoadCursorA@8]
  mov   [wc+WNDCLASS.hCursor],eax

  mov   eax,_WindowMessagesHandler@16
  mov   [wc+WNDCLASS.lpWndProc],eax

  mov   eax,winapp_class
  mov   [wc+WNDCLASS.lpszClassName],eax

  push  wc
  call  dword [__imp__RegisterClassA@4]

  ;-----------------
  ; Cria a nova janela.
  ;-----------------
  push  dword 0
  push  dword [arg_hInst]
  push  dword 0
  push  dword 0
  push  dword 480
  push  dword 640
  push  dword CW_USEDEFAULT
  push  dword CW_USEDEFAULT
  push  dword WS_OVERLAPPEDWINDOW
  push  winapp_title
  push  winapp_class
  push  dword 0
  call  dword [__imp__CreateWindowExA@48]
  test  eax,eax
  jnz   created_ok

  push  dword (MB_OK | MB_ICONERROR)
  push  msg_caption
  push  msg_text
  push  dword 0
  call  dword [__imp__MessageBoxA@16]
  xor   eax,eax
  jmp   WinMainExit

created_ok:
  mov   [hWnd],eax

  ;---- Update and Show...
  push  eax
  call  dword [__imp__UpdateWindow@4]
  push  dword [arg_nCmdShow]
  push  dword [hWnd]
  call  dword [__imp__ShowWindow@8]

MessageLoop:
  push  dword 0
  push  dword 0
  push  msg
  push  dword [hWnd]
  call  dword [__imp__GetMessageA@16]
  test  eax,eax
  jz    ExitLoop

  push  msg
  call  dword [__imp__TranslateMessage@4]

  push  msg
  call  dword [__imp__DispatchMessageA@4]
  
  jmp   MessageLoop

ExitLoop:
  mov   eax,[msg+MSG.wParam]

WinMainExit:
  pop   ebp
  ret   16    
