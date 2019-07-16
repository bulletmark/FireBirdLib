#include                <string.h>
#include                "FBLib_flash.h"

static bool FlashSatTablesDecode_ST_TMSS(TYPE_SatInfo_TMSS *Data, tFlashSatTable *SatTable)
{
  TRACEENTER();

  if(!Data || !SatTable)
  {
    TRACEEXIT();
    return FALSE;
  }

  memcpy(SatTable, Data, sizeof(tFlashSatTable));

  TRACEEXIT();
  return TRUE;
}

static bool FlashSatTablesDecode_ST_TMST(TYPE_SatInfo_TMST *Data, tFlashSatTable *SatTable)
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

static bool FlashSatTablesDecode_ST_TMSC(TYPE_SatInfo_TMSC *Data, tFlashSatTable *SatTable)
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
