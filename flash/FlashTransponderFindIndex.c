#include "FBLib_flash.h"

int FlashTransponderFindIndex(dword SatIndex, dword NetworkID, dword TSID)
{
  int                     TrCount, i;
  tFlashTransponderTable  TransponderTable;

  TrCount = FlashTransponderTablesGetTotal(SatIndex);
  for(i = 0; i < TrCount; i++)
  {
    if(FlashTransponderTablesGetInfo(SatIndex, i, &TransponderTable))
    {
      if((TransponderTable.OriginalNetworkID == NetworkID) && (TransponderTable.TSID == TSID)) return i;
    }
  }

  return -1;
}
