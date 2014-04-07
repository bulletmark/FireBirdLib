#include                "../libFireBird.h"

dword *Appl_GetEvtListHeadInHashByChannelID(ulong64 ChannelID)
{
  TRACEENTER();

  dword *(*__Appl_GetEvtListHeadInHash)(word NetID, word TSID, word ServiceID);

  dword                *ret = NULL;
  word                  NetID, TSID, SID;

  __Appl_GetEvtListHeadInHash = (void*)FIS_fwAppl_GetEvtListHeadInHash();
  if(__Appl_GetEvtListHeadInHash)
  {
    NetID = (ChannelID >>  32) & 0xffff;
    TSID = (ChannelID >>  16) & 0xffff;
    SID = ChannelID & 0xffff;
    ret = __Appl_GetEvtListHeadInHash(NetID, TSID, SID);
  }

  TRACEEXIT();
  return ret;
}
