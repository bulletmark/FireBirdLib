#include                "FBLib_EPG.h"

int                     EPGInfoCacheEntries = 0;
int                     EPGInfoNrEntries = 0;
int                     EPGInfoCurrentEntry = 0;
int                     EPGInfoCacheFile = 0;
dword                   EPGInfoCacheSize = 0;
byte                   *EPGInfoCacheMap = NULL;
TYPE_EPGInfo           *EPGInfoCache = NULL;
tEPGFilter              EPGFilter;
bool                    EPGInfoReverseOrder = FALSE;
dword                   EPGInfoStructSize = 0;
char                    EPGCacheFile[40];
int                     EPGAbortLoad = 0;

int EPGInfo_FindFirst(TYPE_EPGInfo *EPGData)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_FindFirst");
  #endif

  dword                *x;
  byte                  PointerOffset;
  TYPE_EvtInfo         *Evt;

  if(EPGFilter.ChannelFilter)
  {
    if(!EPGFilter.StartCurrent)
    {
      //For whatever reason, the hashed pointer list runs into the wrong direction (from younger to older events)
      x = Appl_GetEvtListHeadInHash(EPGFilter.NetworkID, EPGFilter.TSID, EPGFilter.ServiceID);
      PointerOffset = 0x20;
      EPGInfoReverseOrder = TRUE;
    }
    else
    {
      Evt = Appl_GetSameTimeEvent(EPGFilter.SatIndex, EPGFilter.NetworkID, EPGFilter.TSID, EPGFilter.ServiceID);
      x = (dword*)&Evt->TreeByHash;
      PointerOffset = 0x20;
      EPGInfoReverseOrder = TRUE;
    }
  }
  else
  {
    x = Appl_GetEvtListHeadInUsePool();
    PointerOffset = 0x28;
    EPGInfoReverseOrder = FALSE;
  }

  EPGInfoCacheEntries = EPGInfo_CountEvents(x);
  if(EPGInfoCacheEntries == 0)
  {
    if(EPGData) memset(EPGData, 0, sizeof(TYPE_EPGInfo));

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }
  EPGInfo_CreateCache(EPGInfoCacheEntries);
  EPGInfo_CloneToCache(x, PointerOffset, &EPGFilter);

  EPGInfoCurrentEntry = 0;

  if(EPGInfoNrEntries)
  {
    if(EPGInfoReverseOrder)
    {
      memcpy(EPGData, &EPGInfoCache[EPGInfoNrEntries - 1], sizeof(TYPE_EPGInfo));
    }
    else
    {
      memcpy(EPGData, &EPGInfoCache[0], sizeof(TYPE_EPGInfo));
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return EPGInfoNrEntries;
}
