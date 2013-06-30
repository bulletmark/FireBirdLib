#include                "FBLib_EPG.h"

bool EPGInfo_FindPrev(TYPE_EPGInfo *EPGData)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_FindPrev");
  #endif

  EPGInfoCurrentEntry--;
  bool ret = EPGInfo_FindItem(EPGData, EPGInfoCurrentEntry, FALSE);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
