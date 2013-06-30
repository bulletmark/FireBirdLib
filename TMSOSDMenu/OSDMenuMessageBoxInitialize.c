#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxInitialize(char *Title, char *Text)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuMessageBoxInitialize");
  #endif

  if(InfoBoxOSDRgn)OSDMenuInfoBoxDestroy();

  if(MessageBoxOSDRgn) OSDMenuMessageBoxDestroy();

  OSDMenuLoadStdFonts();

  MessageBox.NrButtons = 0;
  MessageBox.CurrentButton = 0;
  MessageBoxNoNormalMode = FALSE;

  strncpyUC(MessageBox.Title, Title, STDSTRINGSIZE);
  MessageBox.Title[STDSTRINGSIZE - 1] = '\0';

  strncpyUC(MessageBox.Text, Text, STDSTRINGSIZE);
  MessageBox.Text[STDSTRINGSIZE - 1] = '\0';

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
