#include                "FBLib_EPG.h"

bool EPGInfo_FindLast(TYPE_EPGInfo *EPGData)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_FindLast");
  #endif

  bool ret = EPGInfo_FindItem(EPGData, EPGInfoNrEntries - 1, TRUE);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
