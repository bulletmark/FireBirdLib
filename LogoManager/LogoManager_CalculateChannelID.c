#include                <string.h>
#include                <stdlib.h>
#include                "libFireBird.h"
#include                "FBLib_LogoManager.h"

ulong64 LogoManager_CalculateChannelID(word SatLongitude, word NetworkID, word TSID, word ServiceID)
{
  TRACEENTER;

  ulong64 ret = ((ulong64)SatLongitude << 48) | ((ulong64)NetworkID << 32) | ((ulong64)TSID << 16) | ServiceID;

  TRACEEXIT;
  return ret;
}
