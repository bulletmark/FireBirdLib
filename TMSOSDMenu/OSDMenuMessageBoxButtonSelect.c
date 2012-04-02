#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxButtonSelect(dword SelectedButton)
{
  if(SelectedButton >= MessageBox.NrButtons) return;

  MessageBox.CurrentButton = SelectedButton;
  if(MessageBoxOSDRgn) OSDMenuMessageBoxShow();
}
