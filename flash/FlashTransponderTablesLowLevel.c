#include                <string.h>
#include                "FBLib_flash.h"

static bool FlashTransponderTablesDecode_ST_TMSS(TYPE_TpInfo_TMSS *Data, tFlashTransponderTable *TransponderTable)
{
  TRACEENTER();

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
  TransponderTable->unused1           = Data->TPMode;
  TransponderTable->unused2           = Data->unused2;
  TransponderTable->unused3           = Data->unused3;
  TransponderTable->unused4           = Data->unused4;

  TRACEEXIT();
  return TRUE;
}

static bool FlashTransponderTablesDecode_ST_TMST(TYPE_TpInfo_TMST *Data, tFlashTransponderTable *TransponderTable)
{
  TRACEENTER();

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

  TRACEEXIT();
  return TRUE;
}

static bool FlashTransponderTablesDecode_ST_TMSC(TYPE_TpInfo_TMSC *Data, tFlashTransponderTable *TransponderTable)
{
  TRACEENTER();

  memset(TransponderTable, 0, sizeof(tFlashTransponderTable));
  TransponderTable->Frequency         = Data->Frequency >> 8;
  TransponderTable->SymbolRate        = Data->SymbolRate;
  TransponderTable->TSID              = Data->TSID;
  TransponderTable->OriginalNetworkID = Data->OriginalNetworkID;
  TransponderTable->Modulation        = Data->ModulationType;
  TransponderTable->unused1           = Data->unused1;

  TRACEEXIT();
  return TRUE;
}

bool FlashTransponderTablesDecode(void *Data, tFlashTransponderTable *TransponderTable)
{
  TRACEENTER();

  bool ret;

  //TransponderTable is NULL
  if(!Data || !TransponderTable)
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


    case ST_TMSS: ret = FlashTransponderTablesDecode_ST_TMSS(Data, TransponderTable); break;
    case ST_TMST: ret = FlashTransponderTablesDecode_ST_TMST(Data, TransponderTable); break;
    case ST_TMSC: ret = FlashTransponderTablesDecode_ST_TMSC(Data, TransponderTable); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}


static bool FlashTransponderTablesEncode_ST_TMSS(TYPE_TpInfo_TMSS *Data, tFlashTransponderTable *TransponderTable)
{
  TRACEENTER();

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
  Data->TPMode            = TransponderTable->unused1;
  Data->unused2           = TransponderTable->unused2;
  Data->unused3           = TransponderTable->unused3;
  Data->unused4           = TransponderTable->unused4;

  TRACEEXIT();
  return TRUE;
}

static bool FlashTransponderTablesEncode_ST_TMST(TYPE_TpInfo_TMST *Data, tFlashTransponderTable *TransponderTable)
{
  TRACEENTER();

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

  TRACEEXIT();
  return TRUE;
}

static bool FlashTransponderTablesEncode_ST_TMSC(TYPE_TpInfo_TMSC *Data, tFlashTransponderTable *TransponderTable)
{
  TRACEENTER();

  memset(Data, 0, sizeof(TYPE_TpInfo_TMSC));
  Data->Frequency         = TransponderTable->Frequency << 8;
  Data->SymbolRate        = TransponderTable->SymbolRate;
  Data->TSID              = TransponderTable->TSID;
  Data->OriginalNetworkID = TransponderTable->OriginalNetworkID;
  Data->ModulationType    = TransponderTable->Modulation;
  Data->unused1           = TransponderTable->unused1;

  TRACEEXIT();
  return TRUE;
}

bool FlashTransponderTablesEncode(void *Data, tFlashTransponderTable *TransponderTable)
{
  bool ret;

  TRACEENTER();

  //TransponderTable is NULL
  if(!Data || !TransponderTable)
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

    case ST_TMSS: ret = FlashTransponderTablesEncode_ST_TMSS(Data, TransponderTable); break;
    case ST_TMST: ret = FlashTransponderTablesEncode_ST_TMST(Data, TransponderTable); break;
    case ST_TMSC: ret = FlashTransponderTablesEncode_ST_TMSC(Data, TransponderTable); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}
