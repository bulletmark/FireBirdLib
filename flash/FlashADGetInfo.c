#include                <string.h>
#include                "FBLib_flash.h"

bool FlashADGetInfo(tAutoDescrambleTimer *ADTimer)
{
  TRACEENTER;

  bool ret;

  //ADTimer is NULL
  if(!ADTimer)
  {
    TRACEEXIT;
    return FALSE;
  }

  ret = FALSE;
  switch(GetSystemType())
  {
    //Unknown and old 5k/6k systems are not supported
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
      TYPE_AutoDescrambleTimer  *p;

      p = (TYPE_AutoDescrambleTimer*)(FIS_vFlashBlockAutoDec());
      if(p) ret = FlashADDecode(p, ADTimer);
      break;
    }

    case ST_TMST:
    {
      TYPE_AutoDescrambleTimer  *p;

      p = (TYPE_AutoDescrambleTimer*)(FIS_vFlashBlockAutoDec());
      if(p) ret = FlashADDecode(p, ADTimer);
      break;
    }

    case ST_TMSC:
    {
      TYPE_AutoDescrambleTimer  *p;

      p = (TYPE_AutoDescrambleTimer*)(FIS_vFlashBlockAutoDec());
      if(p) ret = FlashADDecode(p, ADTimer);
      break;
    }

    case ST_NRTYPES: break;
  }

  TRACEEXIT;
  return ret;
}
