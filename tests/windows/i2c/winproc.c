#include <windows.h>

#define ID_STATIC1 100
#define ID_STATIC2 101
#define ID_EDIT1   102
#define ID_EDIT2   103
#define ID_BUTTON1 104

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT uMsg,
                         WPARAM wParam,
                         LPARAM lParam)
{
  /* Criarei 5 janelas filhas
   *      (dois labels, dois edit boxes e um botão). */
  static LPSTR ChildClass[5] = { "static", "static", "edit", "button", "edit" };
  static POINT ChildPos[5] = { { 10, 10 }, { 10, 40 }, { 50, 10 }, { 100, 10 }, { 50, 40 } };
  static POINT ChildSize[5] = { { 30, 20 }, { 30, 20 }, { 40, 20 }, { 40, 20 }, { 40, 20 } };
  static DWORD ChildStyleEx[5] = { 0, 0, WS_EX_CLIENTEDGE, 0, WS_EX_CLIENTEDGE };
  static DWORD ChildStyle[5] = { WS_VISIBLE | WS_CHILD | SS_SIMPLE,
                                 WS_VISIBLE | WS_CHILD | SS_SIMPLE,
                                 WS_VISIBLE | WS_CHILD | ES_LEFT,
                                 WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                 WS_VISIBLE | WS_CHILD | ES_LEFT | ES_READONLY
                               };
  static LPSTR ChildCaption[5] = { "Inches:", "Centimeters:", "", "Convert", "" };
  static int ChildId[5] = { ID_STATIC1, ID_STATIC2, ID_EDIT1, ID_BUTTON1, ID_EDIT2 };
  static HWND hChildWnd[5];
  int i;

  switch (uMsg)
  {
  case WM_CREATE:
    for (i = 0; i < 5; i++)
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
        MessageBox(hWnd, "Error creating child window.", "Error", MB_OK | MB_ICONERROR);
        return -1; /* Veja WM_CREATE no MSDN. */
      }
    }

    return 0;

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0L;
  }

  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
