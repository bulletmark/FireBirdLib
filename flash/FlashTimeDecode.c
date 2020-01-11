#include                <string.h>
#include                "FBLib_flash.h"

static bool FlashTimeDecode_ST_TMSS(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo)
{
  TRACEENTER();

  memset(TimeInfo, 0, sizeof(tFlashTimeInfo));
  TimeInfo->UTCOffset      = Data->UTCOffset;
  TimeInfo->SleepTimer     = Data->SleepTimer;
  TimeInfo->unknown1       = Data->unknown1;
  TimeInfo->GMTCollection  = Data->GMTCollection;
  TimeInfo->Mode           = Data->Mode;
  TimeInfo->unknown2       = Data->unknown2;
  TimeInfo->unknown3       = Data->unknown3;
  TimeInfo->DSTActive      = Data->DSTActive;
  TimeInfo->AutoDSTEnabled = Data->AutoDSTEnabled;
  TimeInfo->unknown4       = Data->unknown4;

  TRACEEXIT();
  return TRUE;
}

static bool FlashTimeDecode_ST_TMST(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo)
{
  bool ret;

  TRACEENTER();

  ret = FlashTimeDecode_ST_TMSS(Data, TimeInfo);

  TRACEEXIT();
  return ret;
}

static bool FlashTimeDecode_ST_TMSC(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo)
{
  bool ret;

  TRACEENTER();

  ret = FlashTimeDecode_ST_TMSS(Data, TimeInfo);

  TRACEEXIT();
  return ret;
}

bool FlashTimeDecode(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo)
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

    case ST_TMSS: ret = FlashTimeDecode_ST_TMSS(Data, TimeInfo); break;
    case ST_TMST: ret = FlashTimeDecode_ST_TMST(Data, TimeInfo); break;
    case ST_TMSC: ret = FlashTimeDecode_ST_TMSC(Data, TimeInfo); break;

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}


bool FlashTimeGetInfo(tFlashTimeInfo *TimeInfo)
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
      if(p) ret = FlashTimeDecode(p, TimeInfo);
      break;
    }

    case ST_TMST:
    {
      tFlashTimeInfo   *p;

      p = (tFlashTimeInfo*)(FIS_vFlashBlockTimeInfo());
      if(p) ret = FlashTimeDecode(p, TimeInfo);
      break;
    }

    case ST_TMSC:
    {
      tFlashTimeInfo   *p;

      p = (tFlashTimeInfo*)(FIS_vFlashBlockTimeInfo());
      if(p) ret = FlashTimeDecode(p, TimeInfo);
      break;
    }

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}
