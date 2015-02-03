#include <windows.h>

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

/* Protótipo do tratador de mensagens. */
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance,
                   LPSTR lpszCmdLine, int nCmdShow)
{
  /* Este é o nome da nossa "classe" do objeto de nossa janela. */
  static char MyWindowClass[] = "MyWindowClass";

  MSG message;
  HWND windowHandle;

  /* Define a "classe" da nossa janela. */
  WNDCLASS windowClass = {
    .style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
    .lpfnWndProc = (WNDPROC)WindowProc,
    .hInstance = hInstance,
    .hCursor = LoadCursor(NULL, IDC_ARROW),
    .hbrBackground = (HBRUSH)(COLOR_WINDOW+1),
    .lpszClassName = MyWindowClass
  };

  /* Tenta registrar a nossa classe */
  if (!RegisterClass(&windowClass))
  {
    MessageBox(NULL, "Error registering WindowClass!", "Error!", MB_OK | MB_ICONERROR);
    return 1;
  }

  /* Tenta criar uma janela com base na nossa classe. */
  windowHandle = CreateWindow(MyWindowClass,
                              "Window App Title",
                              WS_OVERLAPPEDWINDOW | WS_POPUPWINDOW,
                              CW_USEDEFAULT, CW_USEDEFAULT, /* x, y */
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              NULL,
                              NULL,
                              hInstance,
                              NULL);

  if (windowHandle == NULL)
  {
    MessageBox(NULL, "Error creating window!", "Error!", MB_OK | MB_ICONERROR);
    return 1;
  }

  ShowWindow(windowHandle, nCmdShow);
  UpdateWindow(windowHandle);   /* Envia o primeiro WM_PAINT */

  /* Loop de coleta de mensagens */
  while (GetMessage(&message, NULL, 0, 0))
  {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }

  return message.wParam;
}

LRESULT CALLBACK WindowProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;

  switch (message) {
    /* Precisamos tratar WM_DESTROY senão a janela jamais será fechada! */
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0L;
  }

  /* Todas as outras mensagens são tratadas pelo tratador default. */
  return DefWindowProc(windowHandle, message, wParam, lParam);  
}

