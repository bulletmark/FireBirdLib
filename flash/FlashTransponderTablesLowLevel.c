#include                <string.h>
#include                "FBLib_flash.h"

bool FlashTransponderTablesDecode(void *Data, tFlashTransponderTable *TransponderTable)
{
  //TransponderTable is NULL
  if(!Data || !TransponderTable) return FALSE;

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

    case ST_TMSS: return FlashTransponderTablesDecode_ST_TMSS(Data, TransponderTable);
    case ST_TMST: return FlashTransponderTablesDecode_ST_TMST(Data, TransponderTable);
    case ST_TMSC: return FlashTransponderTablesDecode_ST_TMSC(Data, TransponderTable);

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashTransponderTablesDecode_ST_TMSS(TYPE_TpInfo_TMSS *Data, tFlashTransponderTable *TransponderTable)
{
  memset(TransponderTable, 0, sizeof(tFlashTransponderTable));
  TransponderTable->SatIndex          = Data->SatIdx;
  TransponderTable->Polarisation      = Data->Polar;
  TransponderTable->ModSystem         = Data->ModulationSystem;
  TransponderTable->Modulation        = Data->ModulationType;
  TransponderTable->FEC               = Data->FECMode;
  TransponderTable->Pilot             = Data->Pilot;
  TransponderTable->Frequency         = Data->Frequency;
  TransponderTable->SymbolRate        = Data->SymbolRate;
  TransponderTable->TSID              = Data->TSID;
  TransponderTable->ClockSync         = Data->AllowTimeSync;
  TransponderTable->OriginalNetworkID = Data->OriginalNetworkID;
  TransponderTable->unused1           = Data->unused1;
  TransponderTable->unused2           = Data->unused2;
  TransponderTable->unused3           = Data->unused3;
  TransponderTable->unused4           = Data->unused4;

  return TRUE;
}

bool FlashTransponderTablesDecode_ST_TMST(TYPE_TpInfo_TMST *Data, tFlashTransponderTable *TransponderTable)
{
  memset(TransponderTable, 0, sizeof(tFlashTransponderTable));
  TransponderTable->SatIndex          = Data->SatIdx;
  TransponderTable->ChannelNr         = Data->ChannelNr;
  TransponderTable->Bandwidth         = Data->Bandwidth;
  TransponderTable->Frequency         = Data->Frequency;
  TransponderTable->TSID              = Data->TSID;
  TransponderTable->LPHP              = Data->LPHP;
  TransponderTable->OriginalNetworkID = Data->OriginalNetworkID;
  TransponderTable->NetworkID         = Data->NetworkID;
  TransponderTable->unused1           = Data->unused1;
  TransponderTable->unused2           = Data->unused2;

  return TRUE;
}

bool FlashTransponderTablesDecode_ST_TMSC(TYPE_TpInfo_TMSC *Data, tFlashTransponderTable *TransponderTable)
{
  memset(TransponderTable, 0, sizeof(tFlashTransponderTable));
  TransponderTable->Frequency         = Data->Frequency >> 8;
  TransponderTable->SymbolRate        = Data->SymbolRate;
  TransponderTable->TSID              = Data->TSID;
  TransponderTable->OriginalNetworkID = Data->OriginalNetworkID;
  TransponderTable->Modulation        = Data->ModulationType;
  TransponderTable->unused1           = Data->unused1;

  return TRUE;
}

bool FlashTransponderTablesEncode(void *Data, tFlashTransponderTable *TransponderTable)
{
  //TransponderTable is NULL
  if(!Data || !TransponderTable) return FALSE;

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

    case ST_TMSS: return FlashTransponderTablesEncode_ST_TMSS(Data, TransponderTable);
    case ST_TMST: return FlashTransponderTablesEncode_ST_TMST(Data, TransponderTable);
    case ST_TMSC: return FlashTransponderTablesEncode_ST_TMSC(Data, TransponderTable);

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashTransponderTablesEncode_ST_TMSS(TYPE_TpInfo_TMSS *Data, tFlashTransponderTable *TransponderTable)
{
  memset(Data, 0, sizeof(TYPE_TpInfo_TMSS));
  Data->SatIdx            = TransponderTable->SatIndex;
  Data->Polar             = TransponderTable->Polarisation;
  Data->ModulationSystem  = TransponderTable->ModSystem;
  Data->ModulationType    = TransponderTable->Modulation;
  Data->FECMode           = TransponderTable->FEC;
  Data->Pilot             = TransponderTable->Pilot;
  Data->Frequency         = TransponderTable->Frequency;
  Data->SymbolRate        = TransponderTable->SymbolRate;
  Data->TSID              = TransponderTable->TSID;
  Data->AllowTimeSync     = TransponderTable->ClockSync;
  Data->OriginalNetworkID = TransponderTable->OriginalNetworkID;
  Data->unused1           = TransponderTable->unused1;
  Data->unused2           = TransponderTable->unused2;
  Data->unused3           = TransponderTable->unused3;
  Data->unused4           = TransponderTable->unused4;

  return TRUE;
}

bool FlashTransponderTablesEncode_ST_TMST(TYPE_TpInfo_TMST *Data, tFlashTransponderTable *TransponderTable)
{
  memset(Data, 0, sizeof(TYPE_TpInfo_TMST));
  Data->SatIdx            = TransponderTable->SatIndex;
  Data->ChannelNr         = TransponderTable->ChannelNr;
  Data->Bandwidth         = TransponderTable->Bandwidth;
  Data->Frequency         = TransponderTable->Frequency;
  Data->TSID              = TransponderTable->TSID;
  Data->LPHP              = TransponderTable->LPHP;
  Data->OriginalNetworkID = TransponderTable->OriginalNetworkID;
  Data->NetworkID         = TransponderTable->NetworkID;
  Data->unused1           = TransponderTable->unused1;
  Data->unused2           = TransponderTable->unused2;

  return TRUE;
}

bool FlashTransponderTablesEncode_ST_TMSC(TYPE_TpInfo_TMSC *Data, tFlashTransponderTable *TransponderTable)
{
  memset(Data, 0, sizeof(TYPE_TpInfo_TMSC));
  Data->Frequency         = TransponderTable->Frequency << 8;
  Data->SymbolRate        = TransponderTable->SymbolRate;
  Data->TSID              = TransponderTable->TSID;
  Data->OriginalNetworkID = TransponderTable->OriginalNetworkID;
  Data->ModulationType    = TransponderTable->Modulation;
  Data->unused1           = TransponderTable->unused1;

  return TRUE;
}
