#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

void LogoManager_Cleanup(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogoManager_Cleanup");
  #endif

  int                   i;

  if(LogoManager_LogoData)
  {
    for(i = 0; i < LogoManager_NrLogos; i++)
      if(LogoManager_LogoData[i].grData) TAP_MemFree(LogoManager_LogoData[i].grData);

    TAP_MemFree(LogoManager_LogoData);
  }

  LogoManager_LogoData = NULL;
  LogoManager_NrLogos = 0;
  LogoManager_LUTInitialized = FALSE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
