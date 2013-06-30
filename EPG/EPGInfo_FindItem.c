#include                "FBLib_EPG.h"

bool EPGInfo_FindItem(TYPE_EPGInfo *EPGData, int EPGIndex, bool EPGReset)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_FindItem");
  #endif

  if((EPGIndex >= EPGInfoNrEntries) || (EPGIndex < 0))
  {
    if(EPGData) memset(EPGData, 0, sizeof(TYPE_EPGInfo));

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(EPGData)
  {
    if(EPGInfoReverseOrder)
    {
      memcpy(EPGData, &EPGInfoCache[EPGInfoNrEntries - EPGIndex - 1], sizeof(TYPE_EPGInfo));
      if(EPGReset) EPGInfoCurrentEntry = EPGIndex;
    }
    else
    {
      memcpy(EPGData, &EPGInfoCache[EPGIndex], sizeof(TYPE_EPGInfo));
      if(EPGReset) EPGInfoCurrentEntry = EPGIndex;
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
