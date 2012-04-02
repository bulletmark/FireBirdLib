#include                <string.h>
#include                "FBLib_flash.h"

bool FlashTimerGetInfo(int TimerIndex, tFlashTimer *TimerInfo)
{
  //TimerIndex out of range
  if((TimerIndex < 0) || (TimerIndex >= TAP_Timer_GetTotalNum())) return FALSE;

  //TimerInfo is NULL
  if(!TimerInfo) return FALSE;

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
      TYPE_Timer_TMSS  *p;

      p = (TYPE_Timer_TMSS*)(FIS_vFlashBlockTimer());
      if(!p) return FALSE;
      p = p + TimerIndex;

      return FlashTimerDecode(p, TimerInfo);
    }

    case ST_TMST:
    {
      //Depending on the firmware, some Australian machines use the sat structures (200 bytes)
      if(FlashTimerStructSize() == 200)
      {
        TYPE_Timer_TMST200  *p;

        p = (TYPE_Timer_TMST200*)(FIS_vFlashBlockTimer());
        if(!p) return FALSE;
        p = p + TimerIndex;

        return FlashTimerDecode(p, TimerInfo);
      }
      else
      {
        TYPE_Timer_TMST  *p;

        p = (TYPE_Timer_TMST*)(FIS_vFlashBlockTimer());
        if(!p) return FALSE;
        p = p + TimerIndex;

        return FlashTimerDecode(p, TimerInfo);
      }
    }

    case ST_TMSC:
    {
      TYPE_Timer_TMSC  *p;

      p = (TYPE_Timer_TMSC*)(FIS_vFlashBlockTimer());
      if(!p) return FALSE;
      p = p + TimerIndex;

      return FlashTimerDecode(p, TimerInfo);
    }

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashTimerDecode(void *Data, tFlashTimer *TimerInfo)
{
  if(!Data || !TimerInfo) return FALSE;

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
      return FlashTimerDecode_ST_TMSS(Data, TimerInfo);
    }

    case ST_TMST:
    {
      //Depending on the firmware, some Australian machines use the sat structures (200 bytes)
      if(FlashTimerStructSize() == 200)
        return FlashTimerDecode_ST_TMST200(Data, TimerInfo);
      else
        return FlashTimerDecode_ST_TMST(Data, TimerInfo);
    }

    case ST_TMSC:
    {
      return FlashTimerDecode_ST_TMSC(Data, TimerInfo);
    }

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashTimerDecode_ST_TMSS(TYPE_Timer_TMSS *Data, tFlashTimer *TimerInfo)
{
  memset(TimerInfo, 0, sizeof(tFlashTimer));

  TimerInfo->TunerIndex       = Data->TunerIndex;
  TimerInfo->RecMode          = Data->RecMode;
  TimerInfo->DemuxPath        = Data->DemuxPath;
  TimerInfo->ManualRec        = Data->ManualRec;
  TimerInfo->unused1          = Data->unused1;
  TimerInfo->SatIndex         = Data->SatIndex;
  TimerInfo->ServiceType      = Data->ServiceType;
  TimerInfo->ReservationType  = Data->ReservationType;
  TimerInfo->unused2          = Data->unused2;
  TimerInfo->ServiceID        = Data->ServiceID;
  TimerInfo->Duration         = Data->Duration;
  TimerInfo->unused3          = Data->unused3;
  strncpy(TimerInfo->FileName, Data->FileName, 130);
  TimerInfo->StartTime        = Data->StartTime;
  TimerInfo->EndTime          = Data->EndTime;
  TimerInfo->PMTPID           = Data->PMTPID;
  TimerInfo->isRec            = Data->isRec;
  TimerInfo->NameSet          = Data->NameSet;
  TimerInfo->unused4          = Data->unused4;
  TimerInfo->EPGMarker        = Data->EPGMarker;
  TimerInfo->unused5          = Data->unused5;
  TimerInfo->unknown1         = Data->unknown1;
  TimerInfo->EventID1         = Data->EventID1;
  TimerInfo->EventID2         = Data->EventID2;
  TimerInfo->ServiceIndex     = Data->ServiceIndex;
  memcpy(TimerInfo->unused8, Data->unused8, 8);
  TimerInfo->IceTV            = Data->IceTV;
  memcpy(TimerInfo->unused9, Data->unused9, 5);

  TimerInfo->TpInfo.SatIndex          = Data->TpInfo.SatIdx;
  TimerInfo->TpInfo.Polarisation      = Data->TpInfo.Polar;
  TimerInfo->TpInfo.ModSystem         = Data->TpInfo.ModulationSystem;
  TimerInfo->TpInfo.Modulation        = Data->TpInfo.ModulationType;
  TimerInfo->TpInfo.FEC               = Data->TpInfo.FECMode;
  TimerInfo->TpInfo.Pilot             = Data->TpInfo.Pilot;
  TimerInfo->TpInfo.Frequency         = Data->TpInfo.Frequency;
  TimerInfo->TpInfo.SymbolRate        = Data->TpInfo.SymbolRate;
  TimerInfo->TpInfo.TSID              = Data->TpInfo.TSID;
  TimerInfo->TpInfo.ClockSync         = Data->TpInfo.AllowTimeSync;
  TimerInfo->TpInfo.OriginalNetworkID = Data->TpInfo.OriginalNetworkID;
  TimerInfo->TpInfo.unused1           = Data->TpInfo.unused1;
  TimerInfo->TpInfo.unused2           = Data->TpInfo.unused2;
  TimerInfo->TpInfo.unused3           = Data->TpInfo.unused3;
  TimerInfo->TpInfo.unused4           = Data->TpInfo.unused4;

  return TRUE;
}

bool FlashTimerDecode_ST_TMST(TYPE_Timer_TMST *Data, tFlashTimer *TimerInfo)
{
  memset(TimerInfo, 0, sizeof(tFlashTimer));

  TimerInfo->TunerIndex       = Data->TunerIndex;
  TimerInfo->RecMode          = Data->RecMode;
  TimerInfo->DemuxPath        = Data->DemuxPath;
  TimerInfo->ManualRec        = Data->ManualRec;
  TimerInfo->unused1          = Data->unused1;
  TimerInfo->SatIndex         = Data->SatIndex;
  TimerInfo->ServiceType      = Data->ServiceType;
  TimerInfo->ReservationType  = Data->ReservationType;
  TimerInfo->unused2          = Data->unused2;
  TimerInfo->ServiceID        = Data->ServiceID;
  TimerInfo->Duration         = Data->Duration;
  TimerInfo->unused3          = Data->unused3;
  strncpy(TimerInfo->FileName, Data->FileName, 130);
  TimerInfo->StartTime        = Data->StartTime;
  TimerInfo->EndTime          = Data->EndTime;
  TimerInfo->PMTPID           = Data->PMTPID;
  TimerInfo->isRec            = Data->isRec;
  TimerInfo->NameSet          = Data->NameSet;
  TimerInfo->unused4          = Data->unused4;
  TimerInfo->EPGMarker        = Data->EPGMarker;
  TimerInfo->unused5          = Data->unused5;
  TimerInfo->unknown1         = Data->unknown1;
  TimerInfo->EventID1         = Data->EventID1;
  TimerInfo->EventID2         = Data->EventID2;
  TimerInfo->ServiceIndex     = Data->ServiceIndex;
  memcpy(TimerInfo->unused8, Data->unused8, 8);
  TimerInfo->IceTV            = Data->IceTV;
  memcpy(TimerInfo->unused9, Data->unused9, 13);

  TimerInfo->TpInfo.SatIndex          = Data->TpInfo.SatIdx;
  TimerInfo->TpInfo.ChannelNr         = Data->TpInfo.ChannelNr;
  TimerInfo->TpInfo.Bandwidth         = Data->TpInfo.Bandwidth;
  TimerInfo->TpInfo.Frequency         = Data->TpInfo.Frequency;
  TimerInfo->TpInfo.TSID              = Data->TpInfo.TSID;
  TimerInfo->TpInfo.LPHP              = Data->TpInfo.LPHP;
  TimerInfo->TpInfo.OriginalNetworkID = Data->TpInfo.OriginalNetworkID;
  TimerInfo->TpInfo.NetworkID         = Data->TpInfo.NetworkID;
  TimerInfo->TpInfo.unused1           = Data->TpInfo.unused1;
  TimerInfo->TpInfo.unused2           = Data->TpInfo.unused2;

  return TRUE;
}

bool FlashTimerDecode_ST_TMST200(TYPE_Timer_TMST200 *Data, tFlashTimer *TimerInfo)
{
  memset(TimerInfo, 0, sizeof(tFlashTimer));

  TimerInfo->TunerIndex       = Data->TunerIndex;
  TimerInfo->RecMode          = Data->RecMode;
  TimerInfo->DemuxPath        = Data->DemuxPath;
  TimerInfo->ManualRec        = Data->ManualRec;
  TimerInfo->unused1          = Data->unused1;
  TimerInfo->SatIndex         = Data->SatIndex;
  TimerInfo->ServiceType      = Data->ServiceType;
  TimerInfo->ReservationType  = Data->ReservationType;
  TimerInfo->unused2          = Data->unused2;
  TimerInfo->ServiceID        = Data->ServiceID;
  TimerInfo->Duration         = Data->Duration;
  TimerInfo->unused3          = Data->unused3;
  strncpy(TimerInfo->FileName, Data->FileName, 130);
  TimerInfo->StartTime        = Data->StartTime;
  TimerInfo->EndTime          = Data->EndTime;
  TimerInfo->PMTPID           = Data->PMTPID;
  TimerInfo->isRec            = Data->isRec;
  TimerInfo->NameSet          = Data->NameSet;
  TimerInfo->unused4          = Data->unused4;
  TimerInfo->EPGMarker        = Data->EPGMarker;
  TimerInfo->unused5          = Data->unused5;
  TimerInfo->unknown1         = Data->unknown1;
  TimerInfo->EventID1         = Data->EventID1;
  TimerInfo->EventID2         = Data->EventID2;
  TimerInfo->ServiceIndex     = Data->ServiceIndex;
  memcpy(TimerInfo->unused8, Data->unused8, 8);
  TimerInfo->IceTV            = Data->IceTV;
  memcpy(TimerInfo->unused9, Data->unused9, 5);

  TimerInfo->TpInfo.SatIndex          = Data->TpInfo.SatIdx;
  TimerInfo->TpInfo.ChannelNr         = Data->TpInfo.ChannelNr;
  TimerInfo->TpInfo.Bandwidth         = Data->TpInfo.Bandwidth;
  TimerInfo->TpInfo.Frequency         = Data->TpInfo.Frequency;
  TimerInfo->TpInfo.TSID              = Data->TpInfo.TSID;
  TimerInfo->TpInfo.LPHP              = Data->TpInfo.LPHP;
  TimerInfo->TpInfo.OriginalNetworkID = Data->TpInfo.OriginalNetworkID;
  TimerInfo->TpInfo.NetworkID         = Data->TpInfo.NetworkID;
  TimerInfo->TpInfo.unused1           = Data->TpInfo.unused1;
  TimerInfo->TpInfo.unused2           = Data->TpInfo.unused2;

  return TRUE;
}

bool FlashTimerDecode_ST_TMSC(TYPE_Timer_TMSC *Data, tFlashTimer *TimerInfo)
{
  memset(TimerInfo, 0, sizeof(tFlashTimer));

  TimerInfo->TunerIndex       = Data->TunerIndex;
  TimerInfo->RecMode          = Data->RecMode;
  TimerInfo->DemuxPath        = Data->DemuxPath;
  TimerInfo->ManualRec        = Data->ManualRec;
  TimerInfo->unused1          = Data->unused1;
  TimerInfo->SatIndex         = Data->SatIndex;
  TimerInfo->ServiceType      = Data->ServiceType;
  TimerInfo->ReservationType  = Data->ReservationType;
  TimerInfo->unused2          = Data->unused2;
  TimerInfo->ServiceID        = Data->ServiceID;
  TimerInfo->Duration         = Data->Duration;
  TimerInfo->unused3          = Data->unused3;
  strncpy(TimerInfo->FileName, Data->FileName, 130);
  TimerInfo->StartTime        = Data->StartTime;
  TimerInfo->EndTime          = Data->EndTime;
  TimerInfo->PMTPID           = Data->PMTPID;
  TimerInfo->isRec            = Data->isRec;
  TimerInfo->NameSet          = Data->NameSet;
  TimerInfo->unused4          = Data->unused4;
  TimerInfo->EPGMarker        = Data->EPGMarker;
  TimerInfo->unused5          = Data->unused5;
  TimerInfo->unknown1         = Data->unknown1;
  TimerInfo->EventID1         = Data->EventID1;
  TimerInfo->EventID2         = Data->EventID2;
  TimerInfo->ServiceIndex     = Data->ServiceIndex;
  memcpy(TimerInfo->unused8, Data->unused8, 8);
  TimerInfo->IceTV            = Data->IceTV;
  memcpy(TimerInfo->unused9, Data->unused9, 5);

  TimerInfo->TpInfo.Frequency         = Data->TpInfo.Frequency;
  TimerInfo->TpInfo.SymbolRate        = Data->TpInfo.SymbolRate;
  TimerInfo->TpInfo.TSID              = Data->TpInfo.TSID;
  TimerInfo->TpInfo.OriginalNetworkID = Data->TpInfo.OriginalNetworkID;
  TimerInfo->TpInfo.Modulation        = Data->TpInfo.ModulationType;
  TimerInfo->TpInfo.unused1           = Data->TpInfo.unused1;

  return TRUE;
}
