#include "FBLib_flash.h"

int FlashTransponderFindIndex(dword SatIndex, dword NetworkID, dword TSID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashTransponderFindIndex");
  #endif

  int                     TrCount, i;
  tFlashTransponderTable  TransponderTable;

  TrCount = FlashTransponderTablesGetTotal(SatIndex);
  for(i = 0; i < TrCount; i++)
  {
    if(FlashTransponderTablesGetInfo(SatIndex, i, &TransponderTable))
    {
      if((TransponderTable.OriginalNetworkID == NetworkID) && (TransponderTable.TSID == TSID))
      {
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return i;
      }
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return -1;
}
