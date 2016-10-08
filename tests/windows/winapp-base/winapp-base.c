/*
   Gabarito de Programa em C para Windows.
 */
#include <windows.h>
#include "winapp-resources.h"

HWND mainWindowHandle;

LRESULT CALLBACK WindowMessageHandler(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine, int nCmdShow)
{
  MSG msg;
  static const char *className = "MyWinAppClass32";
  WNDCLASS wc = {
    .style = CS_HREDRAW | CS_VREDRAW,
    .lpfnWndProc = WindowMessageHandler,
    .hInstance = hInstance,
    .hIcon = LoadIcon(hInstance, "WINAPP_ICON"),
    .hCursor = LoadCursor(NULL, IDC_ARROW),
    .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
    .lpszClassName = className,
    .lpszMenuName = "MAIN_MENU"
  };

  RegisterClass(&wc);

  if ((mainWindowHandle = CreateWindowEx(0,
                            className,
                            "My Win32 App",
                            WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            640, 480,
                            NULL,
                            NULL,
                            hInstance,
                            NULL
                          )) == NULL)
  {
    MessageBox(NULL, "Error creating window!", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  UpdateWindow(mainWindowHandle);
  ShowWindow(mainWindowHandle, nCmdShow);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}

LRESULT CALLBACK WindowMessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  RECT rc;

  switch (uMsg)
  {
  case WM_PAINT:
    BeginPaint(hWnd, &ps);

    /* Pega as coordenadas do retângulo da área cliente */
    GetClientRect(hWnd, &rc);

    /* Desenha o texto usando a fonte atual. */
    DrawText(ps.hdc, "Hello, world", -1, &rc,
             DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    EndPaint(hWnd, &ps);
    break;

  case WM_COMMAND:
    if (LOWORD(wParam) == ID_FILE_EXIT)
      PostMessage(hWnd, WM_CLOSE, 0, 0);
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    break;

  default:
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
  }

  return 0;
}



