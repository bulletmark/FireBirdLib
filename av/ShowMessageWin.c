#include "../libFireBird.h"

void ShowMessageWin(char *title, char *lpMessage1, char *lpMessage2, dword dwDelay)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("ShowMessageWin");
  #endif

  char *content[4];

  content[0] = title;
  content[1] = lpMessage1;
  content[2] = lpMessage2;
  content[3] = NULL;

  ShowMessageWindow(content, 720, 576, FNT_Size_1926, ALIGN_CENTER, RGB(156,156,156), RGB(255,255,82), RGB(230,255,230), RGB(25,41,82), dwDelay);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
