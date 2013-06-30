#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

bool LogoManager_LogosAvailable(tLogoStyle LogoStyle)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogoManager_LogosAvailable");
  #endif

  int                   i;

  for(i = 0; i < LogoManager_NrLogos; i++)
    if(LogoManager_LogoData[i].Style  == LogoStyle)
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return TRUE;
    }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
