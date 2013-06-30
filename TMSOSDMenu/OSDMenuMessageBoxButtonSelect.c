#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxButtonSelect(dword SelectedButton)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuMessageBoxButtonSelect");
  #endif

  if(SelectedButton >= MessageBox.NrButtons)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  MessageBox.CurrentButton = SelectedButton;
  if(MessageBoxOSDRgn) OSDMenuMessageBoxShow();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
