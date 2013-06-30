#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuMessageBoxLastButton(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuMessageBoxLastButton");
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return MessageBox.CurrentButton;
}
