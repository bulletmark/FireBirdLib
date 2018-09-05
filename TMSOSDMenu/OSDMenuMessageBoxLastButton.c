#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuMessageBoxLastButton(void)
{
  TRACEENTER;

  TRACEEXIT;
  return MessageBox.CurrentButton;
}
