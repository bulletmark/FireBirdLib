#include                <string.h>
#include                "../libFireBird.h"

void StrToISOAlloc(byte *SourceString, byte **DestString)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("StrToISOAlloc");
  #endif

  if((SourceString == NULL) || (DestString == NULL))
  {
    if(DestString) *DestString =  NULL;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return;
  }

  *DestString = TAP_MemAlloc(strlenUC(SourceString) + 1);
  StrToISO(SourceString, *DestString);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
