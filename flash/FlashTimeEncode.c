#include                <string.h>
#include                "FBLib_flash.h"

static bool FlashTimeEncode_ST_TMSS(tFlashTimeInfo *TimeInfo, tFlashTimeInfo *Data)
{
  TRACEENTER();

  memset(Data, 0, sizeof(tFlashTimeInfo));
  Data->UTCOffset      = TimeInfo->UTCOffset;
  Data->SleepTimer     = TimeInfo->SleepTimer;
  Data->unknown1       = TimeInfo->unknown1;
  Data->GMTCollection  = TimeInfo->GMTCollection;
  Data->Mode           = TimeInfo->Mode;
  Data->unknown2       = TimeInfo->unknown2;
  Data->unknown3       = TimeInfo->unknown3;
  Data->DSTActive      = TimeInfo->DSTActive;
  Data->AutoDSTEnabled = TimeInfo->AutoDSTEnabled;
  Data->unknown4       = TimeInfo->unknown4;

  TRACEEXIT();
  return TRUE;
}

static bool FlashTimeEncode_ST_TMST(tFlashTimeInfo *TimeInfo, tFlashTimeInfo *Data)
{
  bool ret;

  TRACEENTER();

  ret = FlashTimeEncode_ST_TMSS(TimeInfo, Data);

  TRACEEXIT();
  return ret;
}

static bool FlashTimeEncode_ST_TMSC(tFlashTimeInfo *TimeInfo, tFlashTimeInfo *Data)
{
  bool ret;

  TRACEENTER();

  ret = FlashTimeEncode_ST_TMSS(TimeInfo, Data);

  TRACEEXIT();
  return ret;
}

bool FlashTimeEncode(tFlashTimeInfo *TimeInfo, tFlashTimeInfo *Data)
{
  bool ret;

  TRACEENTER();

  //TimeInfo is NULL
  if(!Data || !TimeInfo)
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

    case ST_TMSS: ret = FlashTimeEncode_ST_TMSS(TimeInfo, Data); break;
    case ST_TMST: ret = FlashTimeEncode_ST_TMST(TimeInfo, Data); break;
    case ST_TMSC: ret = FlashTimeEncode_ST_TMSC(TimeInfo, Data); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}

bool FlashTimeSetInfo(tFlashTimeInfo *TimeInfo)
{
  TRACEENTER();

  bool ret;

  //TimeInfo is NULL
  if(!TimeInfo)
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
      tFlashTimeInfo   *p;

      p = (tFlashTimeInfo*)(FIS_vFlashBlockTimeInfo());
      if(p) ret = FlashTimeEncode(TimeInfo, p);
      break;
    }

    case ST_TMST:
    {
      tFlashTimeInfo   *p;

      p = (tFlashTimeInfo*)(FIS_vFlashBlockTimeInfo());
      if(p) ret = FlashTimeEncode(TimeInfo, p);
      break;
    }

    case ST_TMSC:
    {
      tFlashTimeInfo   *p;

      p = (tFlashTimeInfo*)(FIS_vFlashBlockTimeInfo());
      if(p) ret = FlashTimeEncode(TimeInfo, p);
      break;
    }

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}
