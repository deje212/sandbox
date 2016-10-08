#include <windows.h>
#include <stdio.h>

#define ID_STATIC1 100
#define ID_EDIT1   101
#define ID_BUTTON1 102

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT uMsg,
                         WPARAM wParam,
                         LPARAM lParam)
{
  /* Criarei 5 janelas filhas
   *      (dois labels, dois edit boxes e um botão). */
  static LPSTR ChildClass[3] = { "static", "edit", "button" };
  static POINT ChildPos[3] = { { 10, 10 }, { 60, 10 }, { 10, 40 } };
  static POINT ChildSize[3] = { { 50, 20 }, { 240, 20 }, { 60, 20 } };
  static DWORD ChildStyleEx[3] = { 0, WS_EX_CLIENTEDGE, 0 };
  static DWORD ChildStyle[3] = { WS_VISIBLE | WS_CHILD | SS_SIMPLE,
                                 WS_VISIBLE | WS_CHILD | ES_LEFT,
                                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON };
  static LPSTR ChildCaption[3] = { "Texto:", "", "Mostrar" };
  static int   ChildId[3] = { ID_STATIC1, ID_EDIT1, ID_BUTTON1 };
  static HWND  hChildWnd[3];
  int i;

  switch (uMsg)
  {
  case WM_CREATE:
    for (i = 0; i < 3; i++)
    {
      hChildWnd[i] = CreateWindowEx(ChildStyleEx[i], 
                                    ChildClass[i], 
                                    ChildCaption[i], 
                                    ChildStyle[i],
                                    ChildPos[i].x, ChildPos[i].y,
                                    ChildSize[i].x, ChildSize[i].y,
                                    hWnd,
                                    (HMENU)ChildId[i],
                                    ((LPCREATESTRUCT)lParam)->hInstance,
                                    NULL);

      if (!hChildWnd[i])
      {
        char buf[128];
        sprintf(buf, "Erro criando janela filha (id=%d).", ChildId[i]);

        MessageBox(hWnd, buf, "Error", MB_OK | MB_ICONERROR);
        return -1; /* Veja WM_CREATE no MSDN. */
      }

      SendMessage(hChildWnd[i], WM_SETFONT, 
                  (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 
                  TRUE);
    }

    /* EditBox aceitará, no máximo 100 chars. */
    SendMessage(hChildWnd[1], EM_SETLIMITTEXT, 100, 0);

    return 0;

  case WM_COMMAND:
    if (LOWORD(wParam) == ID_BUTTON1)
    {
      char buf[128];
      SendMessage(hChildWnd[1], WM_GETTEXT, 100, (LPARAM)buf);

      MessageBox(hWnd, buf, "Mensagem", MB_OK);

      return 0;
    }
    break;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0L;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
