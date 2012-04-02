#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxInitialize(char *Title, char *Text)
{
  if(InfoBoxOSDRgn)OSDMenuInfoBoxDestroy();

  if(MessageBoxOSDRgn) OSDMenuMessageBoxDestroy();
  MessageBox.NrButtons = 0;
  MessageBox.CurrentButton = 0;
  MessageBoxNoNormalMode = FALSE;

  strncpy(MessageBox.Title, Title, STDSTRINGSIZE);
  MessageBox.Title[STDSTRINGSIZE - 1] = '\0';

  strncpy(MessageBox.Text, Text, STDSTRINGSIZE);
  MessageBox.Text[STDSTRINGSIZE - 1] = '\0';
}
