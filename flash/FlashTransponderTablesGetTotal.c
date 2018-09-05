#include                "FBLib_flash.h"

int FlashTransponderTablesGetTotal(int SatNum)
{
  TRACEENTER;

  tFlashSatTable        SatTable;

  if((SatNum < 0) || (SatNum >= FlashSatTablesGetTotal()))
  {
    TRACEEXIT;
    return 0;
  }

  if(!FlashSatTablesGetInfo(SatNum, &SatTable))
  {
    TRACEEXIT;
    return 0;
  }

  TRACEEXIT;
  return SatTable.NrOfTransponders;
}
