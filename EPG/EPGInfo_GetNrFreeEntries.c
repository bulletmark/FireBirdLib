#include                "FBLib_EPG.h"

dword EPGInfo_GetNrFreeEntries(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_GetNrFreeEntries");
  #endif

  dword ret = Appl_GetEvtCountInFreePool();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
