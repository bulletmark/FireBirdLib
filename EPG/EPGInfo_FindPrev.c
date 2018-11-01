#include                "FBLib_EPG.h"

bool EPGInfo_FindPrev(TYPE_EPGInfo *EPGData)
{
  TRACEENTER();

  EPGInfoCurrentEntry--;
  bool ret = EPGInfo_FindItem(EPGData, EPGInfoCurrentEntry, FALSE);

  TRACEEXIT();
  return ret;
}
