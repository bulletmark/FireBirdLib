#include                <string.h>
#include                "FBLib_flash.h"

bool FlashTransponderTablesDel(int SatNum, int TransponderNum)
{
  TRACEENTER();

  bool ret;

  //SatNum out of range
  if((SatNum < 0) || (SatNum >= FlashSatTablesGetTotal()))
  {
    TRACEEXIT();
    return FALSE;
  }

  //TransponderNum out of range
  if((TransponderNum < 0) || (TransponderNum >= FlashTransponderTablesGetTotal(SatNum)))
  {
    TRACEEXIT();
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
      TYPE_TpInfo_TMSS       *pTransp, *pTranspEnd;
      TYPE_SatInfo_TMSS      *pSat;
      int                     i, TPIdx, NrSats;
      dword                  *NrTransponders;

      pSat = (TYPE_SatInfo_TMSS*)(FIS_vFlashBlockSatInfo());
      if(!pSat)
      {
        TRACEEXIT();
        return FALSE;
      }

      NrSats = FlashSatTablesGetTotal();

      pTransp = (TYPE_TpInfo_TMSS*)(FIS_vFlashBlockTransponderInfo());
      if(!pTransp)
      {
        TRACEEXIT();
        return FALSE;
      }

      //Find the end of the transponder list
      pTranspEnd = pTransp;
      for(i = 0; i <= NrSats; i++)
      {
        pTranspEnd += (pSat->NrOfTransponders);
        pSat++;
      }

      //Find the location where to delete the transponder
      TPIdx = 0;
      pSat = (TYPE_SatInfo_TMSS*)(FIS_vFlashBlockSatInfo());
      for(i = 0; i < SatNum; i++)
      {
        TPIdx += pSat->NrOfTransponders;
        pSat++;
      }
      pTransp += (TPIdx + TransponderNum);

      //Move all transponders
      while(pTranspEnd > pTransp)
      {
        memcpy(pTransp, pTransp + 1, sizeof(TYPE_TpInfo_TMSS));
        pTransp++;
      }

      //Decrement the number of transponders
      NrTransponders = (dword*)(FIS_vFlashBlockTransponderInfo() - 4);
      *NrTransponders = *NrTransponders - 1;
      pSat->NrOfTransponders--;

      ret = TRUE;
      break;
    }

    case ST_TMST:
    {
      TYPE_TpInfo_TMST       *pTransp, *pTranspEnd;
      TYPE_SatInfo_TMST      *pSat;
      dword                  *NrTransponders;

      pSat = (TYPE_SatInfo_TMST*)(FIS_vFlashBlockSatInfo());
      if(!pSat)
      {
        TRACEEXIT();
        return FALSE;
      }

      pTransp = (TYPE_TpInfo_TMST*)(FIS_vFlashBlockTransponderInfo());
      if(!pTransp)
      {
        TRACEEXIT();
        return FALSE;
      }

      //Find the location where to delete the transponder
      pTransp += TransponderNum;

      //Find the end of the transponder list
      pTranspEnd = pTransp;
      while(pTranspEnd->Frequency) pTranspEnd++;

      //Move all transponders
      while(pTranspEnd > pTransp)
      {
        memcpy(pTransp, pTransp + 1, sizeof(TYPE_TpInfo_TMST));
        pTransp++;
      }

      //Decrement the number of transponders
      NrTransponders = (dword*)(FIS_vFlashBlockTransponderInfo() - 4);
      *NrTransponders = *NrTransponders - 1;
      pSat->NrOfTransponders--;

      ret = TRUE;
      break;
    }

    case ST_TMSC:
    {
      TYPE_TpInfo_TMSC       *pTransp, *pTranspEnd;
      TYPE_SatInfo_TMSC      *pSat;
      dword                  *NrTransponders;

      pSat = (TYPE_SatInfo_TMSC*)(FIS_vFlashBlockSatInfo());
      if(!pSat)
      {
        TRACEEXIT();
        return FALSE;
      }

      pTransp = (TYPE_TpInfo_TMSC*)(FIS_vFlashBlockTransponderInfo());
      if(!pTransp)
      {
        TRACEEXIT();
        return FALSE;
      }

      //Find the location where to delete the transponder
      pTransp += TransponderNum;

      //Find the end of the transponder list
      pTranspEnd = pTransp;
      while(pTranspEnd->Frequency) pTranspEnd++;

      //Move all transponders
      while(pTranspEnd > pTransp)
      {
        memcpy(pTransp, pTransp + 1, sizeof(TYPE_TpInfo_TMSC));
        pTransp++;
      }

      //Decrement the number of transponders
      NrTransponders = (dword*)(FIS_vFlashBlockTransponderInfo() - 4);
      *NrTransponders = *NrTransponders - 1;
      pSat->NrOfTransponders--;

      ret = TRUE;
      break;
    }

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}
