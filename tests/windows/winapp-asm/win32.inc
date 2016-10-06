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

