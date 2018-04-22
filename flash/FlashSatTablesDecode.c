#include                <string.h>
#include                "FBLib_flash.h"

bool FlashSatTablesGetInfo(int SatNum, tFlashSatTable *SatTable)
{
  TRACEENTER();

  bool ret;

  //SatNum out of range
  if((SatNum < 0) || (SatNum >= FlashSatTablesGetTotal()))
  {
    TRACEEXIT();
    return FALSE;
  }

  //SatTable is NULL
  if(!SatTable)
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
      TYPE_SatInfo_TMSS *p;

      p = (TYPE_SatInfo_TMSS*)FIS_vFlashBlockSatInfo();
      if(p)
      {
        p = p + SatNum;
        ret = FlashSatTablesDecode(p, SatTable);
      }
      break;
    }

    case ST_TMST:
    {
      TYPE_SatInfo_TMST *p;

      p = (TYPE_SatInfo_TMST*)FIS_vFlashBlockSatInfo();
      if(p) ret = FlashSatTablesDecode(p, SatTable);
      break;
    }

    case ST_TMSC:
    {
      TYPE_SatInfo_TMSC *p;

      p = (TYPE_SatInfo_TMSC*)FIS_vFlashBlockSatInfo();
      if(p) ret = FlashSatTablesDecode(p, SatTable);
      break;
    }

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}

bool FlashSatTablesDecode(void *Data, tFlashSatTable *SatTable)
{
  bool ret;

  TRACEENTER();

  if(!Data || !SatTable)
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

    case ST_TMSS: ret = FlashSatTablesDecode_ST_TMSS(Data, SatTable); break;
    case ST_TMST: ret = FlashSatTablesDecode_ST_TMST(Data, SatTable); break;
    case ST_TMSC: ret = FlashSatTablesDecode_ST_TMSC(Data, SatTable); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}

bool FlashSatTablesDecode_ST_TMSS(TYPE_SatInfo_TMSS *Data, tFlashSatTable *SatTable)
{
  TRACEENTER();

  if(!Data || !SatTable)
  {
    TRACEEXIT();
    return FALSE;
  }

  memset(SatTable, 0, sizeof(tFlashSatTable));
  SatTable->NrOfTransponders = Data->NrOfTransponders;
  SatTable->unused1          = Data->unused1;
  SatTable->SatPosition      = Data->SatPosition;
  memcpy(SatTable->unknown1,   Data->unknown1, 22);
  memcpy(SatTable->unused2,    Data->unused2, 8);
  strncpy(SatTable->SatName,   Data->SatName, MAX_SatName - 1);

  //LNB 1
  SatTable->LNB[0].LNBSupply            = Data->LNB[0].LNBSupply;
  SatTable->LNB[0].unused1              = Data->LNB[0].unused1;
  SatTable->LNB[0].DiSEqC10             = Data->LNB[0].DiSEqC10;
  SatTable->LNB[0].unused2              = Data->LNB[0].unused2;
  SatTable->LNB[0].DiSEqC12             = Data->LNB[0].DiSEqC12;
  SatTable->LNB[0].UniversalLNB         = Data->LNB[0].UniversalLNB;
  SatTable->LNB[0].Switch22             = Data->LNB[0].Switch22;
  SatTable->LNB[0].LowBand              = Data->LNB[0].LowBand;
  SatTable->LNB[0].HBFrq                = Data->LNB[0].HBFrq;
  SatTable->LNB[0].unused3              = Data->LNB[0].unused3;
  SatTable->LNB[0].LoopThrough          = Data->LNB[0].LoopThrough;
  SatTable->LNB[0].unused4              = Data->LNB[0].unused4;
  SatTable->LNB[0].DiSEqC11             = Data->LNB[0].DiSEqC11;
  memcpy(SatTable->LNB[0].DiSEqC12Flags, Data->LNB[0].DiSEqC12Flags, 3);
  SatTable->LNB[0].UniCableSatPosition  = Data->LNB[0].UniCableSatPosition;
  SatTable->LNB[0].UniCableunused       = Data->LNB[0].UniCableunused;
  SatTable->LNB[0].UniCableUserBand     = Data->LNB[0].UniCableUserBand;
  SatTable->LNB[0].UniCableFrq          = Data->LNB[0].UniCableFrq;
  memcpy(SatTable->LNB[0].unused5, Data->LNB[0].unused5, 2);

  //LNB 2
  SatTable->LNB[1].LNBSupply    = Data->LNB[1].LNBSupply;
  SatTable->LNB[1].unused1      = Data->LNB[1].unused1;
  SatTable->LNB[1].DiSEqC10     = Data->LNB[1].DiSEqC10;
  SatTable->LNB[1].unused2      = Data->LNB[1].unused2;
  SatTable->LNB[1].DiSEqC12     = Data->LNB[1].DiSEqC12;
  SatTable->LNB[1].UniversalLNB = Data->LNB[1].UniversalLNB;
  SatTable->LNB[1].Switch22     = Data->LNB[1].Switch22;
  SatTable->LNB[1].LowBand      = Data->LNB[1].LowBand;
  SatTable->LNB[1].HBFrq        = Data->LNB[1].HBFrq;
  SatTable->LNB[1].unused3      = Data->LNB[1].unused3;
  SatTable->LNB[1].LoopThrough  = Data->LNB[1].LoopThrough;
  SatTable->LNB[1].unused4      = Data->LNB[1].unused4;
  SatTable->LNB[1].DiSEqC11     = Data->LNB[1].DiSEqC11;
  memcpy(SatTable->LNB[1].DiSEqC12Flags, Data->LNB[1].DiSEqC12Flags, 3);
  SatTable->LNB[1].UniCableSatPosition  = Data->LNB[1].UniCableSatPosition;
  SatTable->LNB[1].UniCableunused       = Data->LNB[1].UniCableunused;
  SatTable->LNB[1].UniCableUserBand     = Data->LNB[1].UniCableUserBand;
  SatTable->LNB[1].UniCableFrq          = Data->LNB[1].UniCableFrq;
  memcpy(SatTable->LNB[1].unused5, Data->LNB[1].unused5, 2);

  TRACEEXIT();
  return TRUE;
}

bool FlashSatTablesDecode_ST_TMST(TYPE_SatInfo_TMST *Data, tFlashSatTable *SatTable)
{
  TRACEENTER();

  if(!Data || !SatTable)
  {
    TRACEEXIT();
    return FALSE;
  }

  memset(SatTable, 0, sizeof(tFlashSatTable));
  SatTable->NrOfTransponders = Data->NrOfTransponders;
  strncpy(SatTable->SatName, Data->SatName, MAX_SatName - 1);

  TRACEEXIT();
  return TRUE;
}

bool FlashSatTablesDecode_ST_TMSC(TYPE_SatInfo_TMSC *Data, tFlashSatTable *SatTable)
{
  TRACEENTER();

  if(!Data || !SatTable)
  {
    TRACEEXIT();
    return FALSE;
  }

  memset(SatTable, 0, sizeof(tFlashSatTable));
  SatTable->NrOfTransponders = Data->NrOfTransponders;
  strncpy(SatTable->SatName, "Cable", MAX_SatName - 1);

  TRACEEXIT();
  return TRUE;
}
