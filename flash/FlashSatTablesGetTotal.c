#include                "FBLib_flash.h"

int FlashSatTablesGetTotal(void)
{
  TYPE_SatInfo_TMSS    *SatInfo_TMSS;
  int                   i;

  SatInfo_TMSS = (TYPE_SatInfo_TMSS*)FIS_vFlashBlockSatInfo();
  if(!SatInfo_TMSS) return 0;

  switch(GetSystemType())
  {
    case ST_UNKNOWN:
    case ST_S:
    case ST_ST:
    case ST_T:
    case ST_C:
    case ST_CT:
    case ST_T5700:
    case ST_T5800:
    case ST_TF7k7HDPVR: return 0;

    case ST_TMSS:
    {
      i = 0;
      while(SatInfo_TMSS->NrOfTransponders > 0)
      {
        i++;
        SatInfo_TMSS++;
      }

      return i;
    }

    case ST_TMST:
      return 1;

    case ST_TMSC:
      return 1;

    case ST_NRTYPES: break;
  }

  return 0;
}
