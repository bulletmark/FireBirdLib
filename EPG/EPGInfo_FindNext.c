#include                "FBLib_EPG.h"

bool EPGInfo_FindNext(TYPE_EPGInfo *EPGData)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_FindNext");
  #endif

  EPGInfoCurrentEntry++;
  bool ret = EPGInfo_FindItem(EPGData, EPGInfoCurrentEntry, FALSE);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
