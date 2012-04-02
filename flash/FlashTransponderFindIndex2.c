#include "FBLib_flash.h"

int FlashTransponderFindIndex2(dword SatIndex, dword NetworkID, dword TSID, byte ModSystem)
{
  int                     TrCount, i;
  tFlashTransponderTable  TransponderTable;

  TrCount = FlashTransponderTablesGetTotal(SatIndex);
  for(i = 0; i < TrCount; i++)
  {
    if(FlashTransponderTablesGetInfo(SatIndex, i, &TransponderTable))
    {
      if((TransponderTable.OriginalNetworkID == NetworkID) && (TransponderTable.TSID == TSID) && (TransponderTable.ModSystem == ModSystem)) return i;
    }
  }

  return -1;
}
