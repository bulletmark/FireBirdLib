#include                "FBLib_EPG.h"

bool EPGInfo_FindNext(TYPE_EPGInfo *EPGData)
{
  TRACEENTER;

  EPGInfoCurrentEntry++;
  bool ret = EPGInfo_FindItem(EPGData, EPGInfoCurrentEntry, FALSE);

  TRACEEXIT;
  return ret;
}
