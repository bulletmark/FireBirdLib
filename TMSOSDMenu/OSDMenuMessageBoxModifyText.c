#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxModifyText(char *Text)
{
  TRACEENTER();

  if(MessageBoxOSDRgn)
  {
    strncpy(MessageBox.Text, Text, STDSTRINGSIZE);
    MessageBox.Text[STDSTRINGSIZE - 1] = '\0';
  }

  TRACEEXIT();
}
