#include                "FBLib_flash.h"

int FlashSatTablesGetTotal(void)
{
  TRACEENTER();

  TYPE_SatInfo_TMSS    *SatInfo_TMSS;
  int                   i, ret;

  ret = 0;
  SatInfo_TMSS = (TYPE_SatInfo_TMSS*)FIS_vFlashBlockSatInfo();
  if(SatInfo_TMSS)
  {
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
      case ST_TF7k7HDPVR: break;

      case ST_TMSS:
      {
        i = 0;
        while(SatInfo_TMSS->SatName[0])
        {
          i++;
          SatInfo_TMSS++;
        }

        ret = i;
        break;
      }

      case ST_TMST:
      case ST_TMSC:
      {
        ret = 1;
        break;
      }

      case ST_NRTYPES: break;
    }
  }

  TRACEEXIT();
  return ret;
}
