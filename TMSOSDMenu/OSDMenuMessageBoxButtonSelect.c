#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxButtonSelect(dword SelectedButton)
{
  TRACEENTER();

  if(SelectedButton >= MessageBox.NrButtons)
  {
    TRACEEXIT();
    return;
  }

  MessageBox.CurrentButton = SelectedButton;
  if(MessageBoxOSDRgn) OSDMenuMessageBoxShow();

  TRACEEXIT();
}
