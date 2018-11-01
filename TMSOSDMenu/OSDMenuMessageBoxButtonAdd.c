#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxButtonAdd(char *Text)
{
  TRACEENTER();

  if(MessageBox.NrButtons < MAXMBBUTTONS)
  {
    strncpy(MessageBox.Button[MessageBox.NrButtons], Text, STDSTRINGSIZE);
    MessageBox.Button[MessageBox.NrButtons][STDSTRINGSIZE - 1] = '\0';
    MessageBox.NrButtons++;
  }

  TRACEEXIT();
}
