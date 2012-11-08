#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxModifyText(char *Text)
{
  if(MessageBoxOSDRgn)
  {
    strncpy(MessageBox.Text, Text, STDSTRINGSIZE);
    MessageBox.Text[STDSTRINGSIZE - 1] = '\0';
  }
}
