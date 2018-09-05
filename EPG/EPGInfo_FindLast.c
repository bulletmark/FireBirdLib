#include                "FBLib_EPG.h"

bool EPGInfo_FindLast(TYPE_EPGInfo *EPGData)
{
  TRACEENTER;

  bool ret = EPGInfo_FindItem(EPGData, EPGInfoNrEntries - 1, TRUE);

  TRACEEXIT;
  return ret;
}
