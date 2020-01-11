#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxInitialize(const char *Title, const char *Text)
{
  TRACEENTER();

  if(InfoBoxOSDRgn)OSDMenuInfoBoxDestroy();

  if(MessageBoxOSDRgn) OSDMenuMessageBoxDestroy();

  OSDMenuLoadStdFonts();

  MessageBox.NrButtons = 0;
  MessageBox.CurrentButton = 0;
  MessageBoxNoNormalMode = FALSE;
  MessageBoxAllowScrollOver = FALSE;

  strncpyUC(MessageBox.Title, Title, STDSTRINGSIZE);
  MessageBox.Title[STDSTRINGSIZE - 1] = '\0';

  strncpyUC(MessageBox.Text, Text, STDSTRINGSIZE);
  MessageBox.Text[STDSTRINGSIZE - 1] = '\0';

  TRACEEXIT();
}
