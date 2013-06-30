#include "../libFireBird.h"

dword HDD_TAP_GetIDByFileName(char *TAPFileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_GetIDByFileName");
  #endif

  tTAPInfo              pTAPInfo;

  if(HDD_TAP_GetInfo(TAPFileName, &pTAPInfo))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return pTAPInfo.TAPID;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return 0;
}
