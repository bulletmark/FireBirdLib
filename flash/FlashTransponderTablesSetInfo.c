#include                <string.h>
#include                "FBLib_flash.h"

bool FlashTransponderTablesSetInfo(int SatNum, int TransponderNum, tFlashTransponderTable *TransponderTable)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FlashTransponderTablesSetInfo");
  #endif

  bool ret;

  //SatNum out of range
  if((SatNum < 0) || (SatNum >= FlashSatTablesGetTotal()))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //TransponderNum out of range
  if((TransponderNum < 0) || (TransponderNum >= FlashTransponderTablesGetTotal(SatNum)))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  //TransponderTable is NULL
  if(!TransponderTable)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

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
    case ST_TF7k7HDPVR:
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return FALSE;
    }

    case ST_TMSS:
    {
      TYPE_TpInfo_TMSS *p;
      int               d, i, TPIdx;

      p = (TYPE_TpInfo_TMSS*)(FIS_vFlashBlockTransponderInfo());
      if(!p)
      {
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return FALSE;
      }

      d = *(int*)FIS_vFlashBlockTransponderInfo();
      TPIdx = 0;
      for(i = 0; i < d; i++)
      {
        if(p->SatIdx == SatNum)
        {
          if(TPIdx == TransponderNum) break;

          TPIdx++;
        }
        p++;
      }
      if((i >= d) || (p->SatIdx != SatNum) || (TPIdx != TransponderNum))
      {
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return FALSE;
      }

      ret = FlashTransponderTablesEncode(p, TransponderTable);

      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return ret;
    }

    case ST_TMST:
    {
      TYPE_TpInfo_TMST     *p;

      p = (TYPE_TpInfo_TMST*)FIS_vFlashBlockTransponderInfo();
      if(!p)
      {
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return FALSE;
      }

      p = p + TransponderNum;
      ret = FlashTransponderTablesEncode(p, TransponderTable);;

      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return ret;
    }

    case ST_TMSC:
    {
      TYPE_TpInfo_TMSC     *p;

      p = (TYPE_TpInfo_TMSC*)FIS_vFlashBlockTransponderInfo();
      if(!p)
      {
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return FALSE;
      }

      p = p + TransponderNum;
      ret = FlashTransponderTablesEncode(p, TransponderTable);

      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return ret;
    }

    case ST_NRTYPES: break;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
