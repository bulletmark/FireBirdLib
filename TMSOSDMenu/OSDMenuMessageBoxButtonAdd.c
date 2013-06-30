#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxButtonAdd(char *Text)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuMessageBoxButtonAdd");
  #endif

  if(MessageBox.NrButtons < MAXMBBUTTONS)
  {
    strncpy(MessageBox.Button[MessageBox.NrButtons], Text, STDSTRINGSIZE);
    MessageBox.Button[MessageBox.NrButtons][STDSTRINGSIZE - 1] = '\0';
    MessageBox.NrButtons++;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
