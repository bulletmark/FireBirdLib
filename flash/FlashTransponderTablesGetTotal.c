#include                "FBLib_flash.h"

int FlashTransponderTablesGetTotal(int SatNum)
{
  tFlashSatTable        SatTable;

  if((SatNum < 0) || (SatNum >= FlashSatTablesGetTotal())) return 0;

  if(!FlashSatTablesGetInfo(SatNum, &SatTable)) return 0;

  return SatTable.NrOfTransponders;
}
