/* main.c */
#include <windows.h>

/* Protótipo do procedimento de janela */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(HINSTANCE hInst,
                     HINSTANCE hPrevInst,
                     LPSTR lpszCmdLine,
                     int nCmdShow)
{
  static LPCSTR szClassName = "SimpleAppClass";
  HWND hWnd;
  MSG msg;
  WNDCLASS wc =
  {
    .style = CS_HREDRAW | CS_VREDRAW,
    .lpfnWndProc = WndProc,
    .hInstance = hInst,
    .hIcon = LoadIcon(NULL, IDI_APPLICATION),
    .hCursor = LoadCursor(NULL, IDC_ARROW),
    .hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1),
    .lpszClassName = szClassName
  };

  /* Isso impede que mais que uma instância seja
     executada. Lembre-se que hPrevInst não tem
     função no Win32. Usei aqui o utilitário
     uuidgen para criar uma string única.

     $ uuidgen -r
     e02ba187-0a93-495f-ad77-7eaa48bedd45

     Se CreateMutex falhar, quer dizer que um
     mutex do mesmo nome já foi criado antes!

     Obs: Poderia ter feito o mesmo para o nome
          da classe de janela! */
  #define MUTEX_UUID "e02ba187-0a93-495f-ad77-7eaa48bedd45"
  if (!CreateMutex(NULL, TRUE, MUTEX_UUID))
    return 0;

  RegisterClass(&wc);

  /* Este estilo criará uma janela "normal" que não pode
     ser maximizada ou ter seu tamanho alterado. */
#define WINDOW_STYLE WS_OVERLAPPED  | \
  WS_SYSMENU     | \
  WS_VISIBLE     | \
  WS_BORDER      | \
  WS_MINIMIZEBOX | \
  WS_CAPTION

  if (!(hWnd = CreateWindowEx(0,
                              szClassName,
                              "My Simple App",
                              WINDOW_STYLE,
                              CW_USEDEFAULT, CW_USEDEFAULT,
                              320, 100,
                              NULL, NULL,
                              hInst,
                              NULL)))
  {
    /* Trata erro se não conseguiu criar a janela. */
    MessageBox(NULL, "Erro ao tentar criar a janela da aplicação.",
               "Erro", MB_OK | MB_ICONERROR);
    return 0;
  }

  UpdateWindow(hWnd);
  ShowWindow(hWnd, SW_SHOW); /* Sempre mostra! */

  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}

