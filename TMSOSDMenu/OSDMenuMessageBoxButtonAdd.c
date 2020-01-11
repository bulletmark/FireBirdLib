#include                <string.h>
#include                "FBLib_TMSOSDMenu.h"

void OSDMenuMessageBoxButtonAdd(const char *Text)
{
  TRACEENTER();

  if (Text && (MessageBox.NrButtons < MAXMBBUTTONS))
  {
    strncpy(MessageBox.Button[MessageBox.NrButtons], Text, STDSTRINGSIZE);
    MessageBox.Button[MessageBox.NrButtons][STDSTRINGSIZE - 1] = '\0';
    MessageBox.NrButtons++;
  }

  TRACEEXIT();
}
