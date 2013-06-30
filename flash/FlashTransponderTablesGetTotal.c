#include                "FBLib_flash.h"

int FlashTransponderTablesGetTotal(int SatNum)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashTransponderTablesGetTotal");
  #endif

  tFlashSatTable        SatTable;

  if((SatNum < 0) || (SatNum >= FlashSatTablesGetTotal()))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  if(!FlashSatTablesGetInfo(SatNum, &SatTable))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return SatTable.NrOfTransponders;
}
