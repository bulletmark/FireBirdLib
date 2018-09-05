#include                <string.h>
#include                "FBLib_flash.h"

int FlashTransponderTablesAdd(int SatNum, tFlashTransponderTable *TransponderTable)
{
  TRACEENTER;

  //SatNum out of range
  if((SatNum < 0) || (SatNum >= FlashSatTablesGetTotal()))
  {
    TRACEEXIT;
    return -1;
  }

  //TransponderTable is NULL
  if(!TransponderTable)
  {
    TRACEEXIT;
    return -1;
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
      TRACEEXIT;
      return -1;
    }

    case ST_TMSS:
    {
      TYPE_TpInfo_TMSS       *pTransp, *pTranspEnd;
      TYPE_SatInfo_TMSS      *pSat;
      int                     i, TPIdx, NrSats;
      dword                  *NrTransponders;

      pSat = (TYPE_SatInfo_TMSS*)(FIS_vFlashBlockSatInfo());
      if(!pSat)
      {
        TRACEEXIT;
        return -1;
      }

      NrSats = FlashSatTablesGetTotal();

      pTransp = (TYPE_TpInfo_TMSS*)(FIS_vFlashBlockTransponderInfo());
      if(!pTransp)
      {
        TRACEEXIT;
        return -1;
      }

      //Find the end of the transponder list
      pTranspEnd = pTransp;
      for(i = 0; i <= NrSats; i++)
      {
        pTranspEnd += (pSat->NrOfTransponders);
        pSat++;
      }

      //Find the location where to insert the new transponder
      TPIdx = 0;
      pSat = (TYPE_SatInfo_TMSS*)(FIS_vFlashBlockSatInfo());
      for(i = 0; i <= SatNum; i++)
      {
        TPIdx += pSat->NrOfTransponders;
        pSat++;
      }
      pSat--;
      pTransp += TPIdx;

      //Create a hole for the new transponder
      while(pTranspEnd > pTransp)
      {
        memcpy(pTranspEnd, pTranspEnd - 1, sizeof(TYPE_TpInfo_TMSS));
        pTranspEnd--;
      }

      //Write the new transponder
      if(FlashTransponderTablesEncode(pTransp, TransponderTable))
      {
        //Increment the number of transponders
        NrTransponders = (dword*)(FIS_vFlashBlockTransponderInfo() - 4);
        *NrTransponders = *NrTransponders + 1;
        pSat->NrOfTransponders++;

        TRACEEXIT;
        return pSat->NrOfTransponders - 1;
      }

      TRACEEXIT;
      return -1;
    }

    case ST_TMST:
    {
      TYPE_TpInfo_TMST       *pTransp;
      TYPE_SatInfo_TMST      *pSat;
      dword                  *NrTransponders;

      pSat = (TYPE_SatInfo_TMST*)(FIS_vFlashBlockSatInfo());
      if(!pSat)
      {
        TRACEEXIT;
        return -1;
      }

      pTransp = (TYPE_TpInfo_TMST*)(FIS_vFlashBlockTransponderInfo());
      if(!pTransp)
      {
        TRACEEXIT;
        return -1;
      }

      //Find the location where to insert the new transponder
      pTransp += pSat->NrOfTransponders;

      //Write the new transponder
      if(FlashTransponderTablesEncode(pTransp, TransponderTable))
      {
        //Increment number of transponders
        NrTransponders = (dword*)(FIS_vFlashBlockTransponderInfo() - 4);
        *NrTransponders = *NrTransponders + 1;
        pSat->NrOfTransponders++;

        TRACEEXIT;
        return pSat->NrOfTransponders - 1;
      }

      TRACEEXIT;
      return -1;
    }

    case ST_TMSC:
    {
      TYPE_TpInfo_TMSC       *pTransp;
      TYPE_SatInfo_TMSC      *pSat;
      dword                  *NrTransponders;

      pSat = (TYPE_SatInfo_TMSC*)(FIS_vFlashBlockSatInfo());
      if(!pSat)
      {
        TRACEEXIT;
        return -1;
      }

      pTransp = (TYPE_TpInfo_TMSC*)(FIS_vFlashBlockTransponderInfo());
      if(!pTransp)
      {
        TRACEEXIT;
        return -1;
      }

      //Find the location where to insert the new transponder
      pTransp += pSat->NrOfTransponders;

      //Write the new transponder
      if(FlashTransponderTablesEncode(pTransp, TransponderTable))
      {
        //Increment number of transponders
        NrTransponders = (dword*)(FIS_vFlashBlockTransponderInfo() - 4);
        *NrTransponders = *NrTransponders + 1;
        pSat->NrOfTransponders++;

        TRACEEXIT;
        return pSat->NrOfTransponders - 1;
      }

      TRACEEXIT;
      return -1;
    }

    case ST_NRTYPES: break;
  }

  TRACEEXIT;
  return -1;
}
