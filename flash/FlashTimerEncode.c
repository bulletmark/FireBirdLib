#include                <string.h>
#include                "FBLib_flash.h"

bool FlashTimerSetInfo(int TimerIndex, tFlashTimer *TimerInfo)
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

      return FlashTimerEncode(p, TimerInfo);
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

        return FlashTimerEncode(p, TimerInfo);
      }
      else
      {
        TYPE_Timer_TMST  *p;

        p = (TYPE_Timer_TMST*)(FIS_vFlashBlockTimer());
        if(!p) return FALSE;
        p = p + TimerIndex;

        return FlashTimerEncode(p, TimerInfo);
      }
    }

    case ST_TMSC:
    {
      TYPE_Timer_TMSC  *p;

      p = (TYPE_Timer_TMSC*)(FIS_vFlashBlockTimer());
      if(!p) return FALSE;
      p = p + TimerIndex;

      return FlashTimerEncode(p, TimerInfo);
    }

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashTimerEncode(void *Data, tFlashTimer *TimerInfo)
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
      return FlashTimerEncode_ST_TMSS(Data, TimerInfo);
    }

    case ST_TMST:
    {
      //Depending on the firmware, some Australian machines use the sat structures (200 bytes)
      if(FlashTimerStructSize() == 200)
        return FlashTimerEncode_ST_TMST200(Data, TimerInfo);
      else
        return FlashTimerEncode_ST_TMST(Data, TimerInfo);
    }

    case ST_TMSC:
    {
      return FlashTimerEncode_ST_TMSC(Data, TimerInfo);
    }

    case ST_NRTYPES: break;
  }

  return FALSE;
}

bool FlashTimerEncode_ST_TMSS(TYPE_Timer_TMSS *Data, tFlashTimer *TimerInfo)
{
  memset(Data, 0, sizeof(TYPE_Timer_TMSS));

  Data->TunerIndex            = TimerInfo->TunerIndex;
  Data->RecMode               = TimerInfo->RecMode;
  Data->DemuxPath             = TimerInfo->DemuxPath;
  Data->ManualRec             = TimerInfo->ManualRec;
  Data->unused1               = TimerInfo->unused1;
  Data->SatIndex              = TimerInfo->SatIndex;
  Data->ServiceType           = TimerInfo->ServiceType;
  Data->ReservationType       = TimerInfo->ReservationType;
  Data->unused2               = TimerInfo->unused2;
  Data->ServiceID             = TimerInfo->ServiceID;
  Data->Duration              = TimerInfo->Duration;
  Data->unused3               = TimerInfo->unused3;
  strncpy(Data->FileName, TimerInfo->FileName, 130);
  Data->StartTime             = TimerInfo->StartTime;
  Data->EndTime               = TimerInfo->EndTime;
  Data->PMTPID                = TimerInfo->PMTPID;
  Data->isRec                 = TimerInfo->isRec;
  Data->NameSet               = TimerInfo->NameSet;
  Data->unused4               = TimerInfo->unused4;
  Data->EPGMarker             = TimerInfo->EPGMarker;
  Data->unused5               = TimerInfo->unused5;
  Data->unknown1              = TimerInfo->unknown1;
  Data->EventID1              = TimerInfo->EventID1;
  Data->EventID2              = TimerInfo->EventID2;
  Data->ServiceIndex          = TimerInfo->ServiceIndex;
  memcpy(Data->unused8, TimerInfo->unused8, 8);
  Data->IceTV                 = TimerInfo->IceTV;
  memcpy(Data->unused9, TimerInfo->unused9, 5);

  Data->TpInfo.SatIdx             = TimerInfo->TpInfo.SatIndex;
  Data->TpInfo.Polar              = TimerInfo->TpInfo.Polarisation;
  Data->TpInfo.ModulationSystem   = TimerInfo->TpInfo.ModSystem;
  Data->TpInfo.ModulationType     = TimerInfo->TpInfo.Modulation;
  Data->TpInfo.FECMode            = TimerInfo->TpInfo.FEC;
  Data->TpInfo.Pilot              = TimerInfo->TpInfo.Pilot;
  Data->TpInfo.Frequency          = TimerInfo->TpInfo.Frequency;
  Data->TpInfo.SymbolRate         = TimerInfo->TpInfo.SymbolRate;
  Data->TpInfo.TSID               = TimerInfo->TpInfo.TSID;
  Data->TpInfo.AllowTimeSync      = TimerInfo->TpInfo.ClockSync;
  Data->TpInfo.OriginalNetworkID  = TimerInfo->TpInfo.OriginalNetworkID;
  Data->TpInfo.unused1            = TimerInfo->TpInfo.unused1;
  Data->TpInfo.unused2            = TimerInfo->TpInfo.unused2;
  Data->TpInfo.unused3            = TimerInfo->TpInfo.unused3;
  Data->TpInfo.unused4            = TimerInfo->TpInfo.unused4;

  return TRUE;
}

bool FlashTimerEncode_ST_TMST(TYPE_Timer_TMST *Data, tFlashTimer *TimerInfo)
{
  memset(Data, 0, sizeof(TYPE_Timer_TMST));

  Data->TunerIndex            = TimerInfo->TunerIndex;
  Data->RecMode               = TimerInfo->RecMode;
  Data->DemuxPath             = TimerInfo->DemuxPath;
  Data->ManualRec             = TimerInfo->ManualRec;
  Data->unused1               = TimerInfo->unused1;
  Data->SatIndex              = TimerInfo->SatIndex;
  Data->ServiceType           = TimerInfo->ServiceType;
  Data->ReservationType       = TimerInfo->ReservationType;
  Data->unused2               = TimerInfo->unused2;
  Data->ServiceID             = TimerInfo->ServiceID;
  Data->Duration              = TimerInfo->Duration;
  Data->unused3               = TimerInfo->unused3;
  strncpy(Data->FileName, TimerInfo->FileName, 130);
  Data->StartTime             = TimerInfo->StartTime;
  Data->EndTime               = TimerInfo->EndTime;
  Data->PMTPID                = TimerInfo->PMTPID;
  Data->isRec                 = TimerInfo->isRec;
  Data->NameSet               = TimerInfo->NameSet;
  Data->unused4               = TimerInfo->unused4;
  Data->EPGMarker             = TimerInfo->EPGMarker;
  Data->unused5               = TimerInfo->unused5;
  Data->unknown1              = TimerInfo->unknown1;
  Data->EventID1              = TimerInfo->EventID1;
  Data->EventID2              = TimerInfo->EventID2;
  Data->ServiceIndex          = TimerInfo->ServiceIndex;
  memcpy(Data->unused8, TimerInfo->unused8, 8);
  Data->IceTV                 = TimerInfo->IceTV;
  memcpy(Data->unused9, TimerInfo->unused9, 13);

  Data->TpInfo.SatIdx               = TimerInfo->TpInfo.SatIndex;
  Data->TpInfo.ChannelNr            = TimerInfo->TpInfo.ChannelNr;
  Data->TpInfo.Bandwidth            = TimerInfo->TpInfo.Bandwidth;
  Data->TpInfo.Frequency            = TimerInfo->TpInfo.Frequency;
  Data->TpInfo.TSID                 = TimerInfo->TpInfo.TSID;
  Data->TpInfo.LPHP                 = TimerInfo->TpInfo.LPHP;
  Data->TpInfo.OriginalNetworkID    = TimerInfo->TpInfo.OriginalNetworkID;
  Data->TpInfo.NetworkID            = TimerInfo->TpInfo.NetworkID;
  Data->TpInfo.unused1              = TimerInfo->TpInfo.unused1;
  Data->TpInfo.unused2              = TimerInfo->TpInfo.unused2;

  return TRUE;
}

bool FlashTimerEncode_ST_TMST200(TYPE_Timer_TMST200 *Data, tFlashTimer *TimerInfo)
{
  memset(Data, 0, sizeof(TYPE_Timer_TMST200));

  Data->TunerIndex            = TimerInfo->TunerIndex;
  Data->RecMode               = TimerInfo->RecMode;
  Data->DemuxPath             = TimerInfo->DemuxPath;
  Data->ManualRec             = TimerInfo->ManualRec;
  Data->unused1               = TimerInfo->unused1;
  Data->SatIndex              = TimerInfo->SatIndex;
  Data->ServiceType           = TimerInfo->ServiceType;
  Data->ReservationType       = TimerInfo->ReservationType;
  Data->unused2               = TimerInfo->unused2;
  Data->ServiceID             = TimerInfo->ServiceID;
  Data->Duration              = TimerInfo->Duration;
  Data->unused3               = TimerInfo->unused3;
  strncpy(Data->FileName, TimerInfo->FileName, 130);
  Data->StartTime             = TimerInfo->StartTime;
  Data->EndTime               = TimerInfo->EndTime;
  Data->PMTPID                = TimerInfo->PMTPID;
  Data->isRec                 = TimerInfo->isRec;
  Data->NameSet               = TimerInfo->NameSet;
  Data->unused4               = TimerInfo->unused4;
  Data->EPGMarker             = TimerInfo->EPGMarker;
  Data->unused5               = TimerInfo->unused5;
  Data->unknown1              = TimerInfo->unknown1;
  Data->EventID1              = TimerInfo->EventID1;
  Data->EventID2              = TimerInfo->EventID2;
  Data->ServiceIndex          = TimerInfo->ServiceIndex;
  memcpy(Data->unused8, TimerInfo->unused8, 8);
  Data->IceTV                 = TimerInfo->IceTV;
  memcpy(Data->unused9, TimerInfo->unused9, 5);

  Data->TpInfo.SatIdx               = TimerInfo->TpInfo.SatIndex;
  Data->TpInfo.ChannelNr            = TimerInfo->TpInfo.ChannelNr;
  Data->TpInfo.Bandwidth            = TimerInfo->TpInfo.Bandwidth;
  Data->TpInfo.Frequency            = TimerInfo->TpInfo.Frequency;
  Data->TpInfo.TSID                 = TimerInfo->TpInfo.TSID;
  Data->TpInfo.LPHP                 = TimerInfo->TpInfo.LPHP;
  Data->TpInfo.OriginalNetworkID    = TimerInfo->TpInfo.OriginalNetworkID;
  Data->TpInfo.NetworkID            = TimerInfo->TpInfo.NetworkID;
  Data->TpInfo.unused1              = TimerInfo->TpInfo.unused1;
  Data->TpInfo.unused2              = TimerInfo->TpInfo.unused2;

  return TRUE;
}

bool FlashTimerEncode_ST_TMSC(TYPE_Timer_TMSC *Data, tFlashTimer *TimerInfo)
{
  memset(Data, 0, sizeof(TYPE_Timer_TMSC));

  Data->TunerIndex            = TimerInfo->TunerIndex;
  Data->RecMode               = TimerInfo->RecMode;
  Data->DemuxPath             = TimerInfo->DemuxPath;
  Data->ManualRec             = TimerInfo->ManualRec;
  Data->unused1               = TimerInfo->unused1;
  Data->SatIndex              = TimerInfo->SatIndex;
  Data->ServiceType           = TimerInfo->ServiceType;
  Data->ReservationType       = TimerInfo->ReservationType;
  Data->unused2               = TimerInfo->unused2;
  Data->ServiceID             = TimerInfo->ServiceID;
  Data->Duration              = TimerInfo->Duration;
  Data->unused3               = TimerInfo->unused3;
  strncpy(Data->FileName, TimerInfo->FileName, 130);
  Data->StartTime             = TimerInfo->StartTime;
  Data->EndTime               = TimerInfo->EndTime;
  Data->PMTPID                = TimerInfo->PMTPID;
  Data->isRec                 = TimerInfo->isRec;
  Data->NameSet               = TimerInfo->NameSet;
  Data->unused4               = TimerInfo->unused4;
  Data->EPGMarker             = TimerInfo->EPGMarker;
  Data->unused5               = TimerInfo->unused5;
  Data->unknown1              = TimerInfo->unknown1;
  Data->EventID1              = TimerInfo->EventID1;
  Data->EventID2              = TimerInfo->EventID2;
  Data->ServiceIndex          = TimerInfo->ServiceIndex;
  memcpy(Data->unused8, TimerInfo->unused8, 8);
  Data->IceTV                 = TimerInfo->IceTV;
  memcpy(Data->unused9, TimerInfo->unused9, 5);

  Data->TpInfo.Frequency            = TimerInfo->TpInfo.Frequency;
  Data->TpInfo.SymbolRate           = TimerInfo->TpInfo.SymbolRate;
  Data->TpInfo.TSID                 = TimerInfo->TpInfo.TSID;
  Data->TpInfo.OriginalNetworkID    = TimerInfo->TpInfo.OriginalNetworkID;
  Data->TpInfo.ModulationType       = TimerInfo->TpInfo.Modulation;
  Data->TpInfo.unused1              = TimerInfo->TpInfo.unused1;

  return TRUE;
}
