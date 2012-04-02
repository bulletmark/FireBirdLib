#include                <string.h>
#include                "FBLib_flash.h"

bool FlashSatTablesGetInfo(int SatNum, tFlashSatTable *SatTable)
{
  //SatNum out of range
  if((SatNum < 0) || (SatNum >= FlashSatTablesGetTotal())) return FALSE;

  //SatTable is NULL
  if(!SatTable) return FALSE;

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
    case ST_TF7k7HDPVR: return FALSE;

    case ST_TMSS:
    {
      TYPE_SatInfo_TMSS *p;

      p = (TYPE_SatInfo_TMSS*)FIS_vFlashBlockSatInfo();
      if(!p) return FALSE;
      p = p + SatNum;
      return FlashSatTablesDecode(p, SatTable);
    }

    case ST_TMST:
    {
      TYPE_SatInfo_TMST *p;

      p = (TYPE_SatInfo_TMST*)FIS_vFlashBlockSatInfo();
      if(!p) return FALSE;
      return FlashSatTablesDecode(p, SatTable);
    }

    case ST_TMSC:
    {
      TYPE_SatInfo_TMSC *p;

      p = (TYPE_SatInfo_TMSC*)FIS_vFlashBlockSatInfo();
      if(!p) return FALSE;

      return FlashSatTablesDecode(p, SatTable);
    }

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashSatTablesDecode(void *Data, tFlashSatTable *SatTable)
{
  if(!Data || !SatTable) return FALSE;

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
    case ST_TF7k7HDPVR: return FALSE;

    case ST_TMSS: return FlashSatTablesDecode_ST_TMSS(Data, SatTable);
    case ST_TMST: return FlashSatTablesDecode_ST_TMST(Data, SatTable);
    case ST_TMSC: return FlashSatTablesDecode_ST_TMSC(Data, SatTable);

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashSatTablesDecode_ST_TMSS(TYPE_SatInfo_TMSS *Data, tFlashSatTable *SatTable)
{
  if(!Data || !SatTable) return FALSE;

  memset(SatTable, 0, sizeof(tFlashSatTable));
  SatTable->NrOfTransponders = Data->NrOfTransponders;
  SatTable->unused1          = Data->unused1;
  SatTable->SatPosition      = Data->SatPosition;
  memcpy(SatTable->unknown1, Data->unknown1, 22);
  memcpy(SatTable->unused2, Data->unused2, 8);
  strncpy(SatTable->SatName, Data->SatName, 15);

  //LNB 1
  SatTable->LNB[0].LNBSupply    = Data->LNB[0].LNBSupply;
  SatTable->LNB[0].unused1      = Data->LNB[0].unused1;
  SatTable->LNB[0].DiSEqC10     = Data->LNB[0].DiSEqC10;
  SatTable->LNB[0].unused2      = Data->LNB[0].unused2;
  SatTable->LNB[0].DiSEqC12     = Data->LNB[0].DiSEqC12;
  SatTable->LNB[0].UniversalLNB = Data->LNB[0].UniversalLNB;
  SatTable->LNB[0].Switch22     = Data->LNB[0].Switch22;
  SatTable->LNB[0].LowBand      = Data->LNB[0].LowBand;
  SatTable->LNB[0].HBFrq        = Data->LNB[0].HBFrq;
  SatTable->LNB[0].unused3      = Data->LNB[0].unused3;
  SatTable->LNB[0].LoopThrough  = Data->LNB[0].LoopThrough;
  SatTable->LNB[0].unused4      = Data->LNB[0].unused4;
  SatTable->LNB[0].DiSEqC11     = Data->LNB[0].DiSEqC11;
  memcpy(SatTable->LNB[0].DiSEqC12Flags, Data->LNB[0].DiSEqC12Flags, 3);
  memcpy(SatTable->LNB[0].unused5, Data->LNB[0].unused5, 5);

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
  memcpy(SatTable->LNB[1].unused5, Data->LNB[1].unused5, 5);

  return TRUE;
}

bool FlashSatTablesDecode_ST_TMST(TYPE_SatInfo_TMST *Data, tFlashSatTable *SatTable)
{
  if(!Data || !SatTable) return FALSE;

  memset(SatTable, 0, sizeof(tFlashSatTable));
  SatTable->NrOfTransponders = Data->NrOfTransponders;
  strncpy(SatTable->SatName, Data->SatName, 15);

  return TRUE;
}

bool FlashSatTablesDecode_ST_TMSC(TYPE_SatInfo_TMSC *Data, tFlashSatTable *SatTable)
{
  if(!Data || !SatTable) return FALSE;

  memset(SatTable, 0, sizeof(tFlashSatTable));
  SatTable->NrOfTransponders = Data->NrOfTransponders;
  strncpy(SatTable->SatName, "Cable", 15);

  return TRUE;
}
