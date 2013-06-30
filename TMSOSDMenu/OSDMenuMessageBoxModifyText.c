#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxModifyText(char *Text)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuMessageBoxModifyText");
  #endif

  if(MessageBoxOSDRgn)
  {
    strncpy(MessageBox.Text, Text, STDSTRINGSIZE);
    MessageBox.Text[STDSTRINGSIZE - 1] = '\0';
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
