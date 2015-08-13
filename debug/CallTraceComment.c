#include                <stdlib.h>
#include                "FBLib_debug.h"

void CallTraceComment(char *Comment)
{
  char                  Spaces[101];
  byte                 *ISOText;

  if(Comment)
  {
    if(!CallTraceInitialized) CallTraceInit();

    Spaces[0] = '\0';

    if(CallTraceEnabled)
    {
      memset(Spaces, ' ', CallLevel < 50 ? CallLevel << 1 : 100);
      Spaces[CallLevel < CTSTACKSIZE ? CallLevel << 1 : 100] = '\0';

      StrToISOAlloc(Comment, &ISOText);
      if(ISOText && *ISOText) TAP_PrintNet("%s# %s\n", Spaces, ISOText);
      TAP_MemFree(ISOText);
    }
  }
}
