#include                <string.h>
#include                "FBLib_flash.h"

bool FlashTimeGetInfo(tFlashTimeInfo *TimeInfo)
{
  //TimeInfo is NULL
  if(!TimeInfo) return FALSE;

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
      tFlashTimeInfo   *p;

      p = (tFlashTimeInfo*)(FIS_vFlashBlockTimeInfo());
      if(!p) return FALSE;

      return FlashTimeDecode(p, TimeInfo);
    }

    case ST_TMST:
    {
      tFlashTimeInfo   *p;

      p = (tFlashTimeInfo*)(FIS_vFlashBlockTimeInfo());
      if(!p) return FALSE;

      return FlashTimeDecode(p, TimeInfo);
    }

    case ST_TMSC:
    {
      tFlashTimeInfo   *p;

      p = (tFlashTimeInfo*)(FIS_vFlashBlockTimeInfo());
      if(!p) return FALSE;

      return FlashTimeDecode(p, TimeInfo);
    }

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashTimeDecode(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo)
{
  //TimeInfo is NULL
  if(!Data || !TimeInfo) return FALSE;

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

    case ST_TMSS: return FlashTimeDecode_ST_TMSS(Data, TimeInfo);
    case ST_TMST: return FlashTimeDecode_ST_TMST(Data, TimeInfo);
    case ST_TMSC: return FlashTimeDecode_ST_TMSC(Data, TimeInfo);

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashTimeDecode_ST_TMSS(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo)
{
  memset(TimeInfo, 0, sizeof(tFlashTimeInfo));
  TimeInfo->UTCOffset     = Data->UTCOffset;
  TimeInfo->SleepTimer    = Data->SleepTimer;
  TimeInfo->unknown1      = Data->unknown1;
  TimeInfo->GMTCollection = Data->GMTCollection;
  TimeInfo->Mode          = Data->Mode;
  TimeInfo->unknown2      = Data->unknown2;
  TimeInfo->unknown3      = Data->unknown3;
  TimeInfo->DST           = Data->DST;
  TimeInfo->unknown4      = Data->unknown4;
  TimeInfo->unknown5      = Data->unknown5;

  return TRUE;
}

bool FlashTimeDecode_ST_TMST(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo)
{
  return FlashTimeDecode_ST_TMSS(Data, TimeInfo);
}

bool FlashTimeDecode_ST_TMSC(tFlashTimeInfo *Data, tFlashTimeInfo *TimeInfo)
{
  return FlashTimeDecode_ST_TMSS(Data, TimeInfo);
}
