#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

ulong64 LogoManager_CalculateChannelID(word SatLongitude, word NetworkID, word TSID, word ServiceID)
{
  return ((ulong64)SatLongitude << 48) | ((ulong64)NetworkID << 32) | (TSID << 16) | ServiceID;
}
