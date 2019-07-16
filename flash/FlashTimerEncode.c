#include                <string.h>
#include                "FBLib_flash.h"

static bool FlashTimerEncode_ST_TMSS(TYPE_Timer_TMSS *Data, tFlashTimer *TimerInfo)
{
  TRACEENTER();

  memset(Data, 0, sizeof(TYPE_Timer_TMSS));

  Data->TimerInfo.TunerIndex            = TimerInfo->TunerIndex;
  Data->TimerInfo.RecMode               = TimerInfo->RecMode;
  Data->TimerInfo.DemuxPath             = TimerInfo->DemuxPath;
  Data->TimerInfo.ManualRec             = TimerInfo->ManualRec;
  Data->TimerInfo.unused1               = TimerInfo->unused1;
  Data->TimerInfo.SatIndex              = TimerInfo->SatIndex;
  Data->TimerInfo.ServiceType           = TimerInfo->ServiceType;
  Data->TimerInfo.ReservationType       = TimerInfo->ReservationType;
  Data->TimerInfo.unused2               = TimerInfo->unused2;
  Data->TimerInfo.ServiceID             = TimerInfo->ServiceID;
  Data->TimerInfo.Duration              = TimerInfo->Duration;
  Data->TimerInfo.unused3               = TimerInfo->unused3;
  strncpy(Data->TimerInfo.FileName, TimerInfo->FileName, 130);
  Data->TimerInfo.StartTime             = TimerInfo->StartTime;
  Data->TimerInfo.EndTime               = TimerInfo->EndTime;
  Data->TimerInfo.PMTPID                = TimerInfo->PMTPID;
  Data->TimerInfo.isRec                 = TimerInfo->isRec;
  Data->TimerInfo.NameSet               = TimerInfo->NameSet;
  Data->TimerInfo.unused4               = TimerInfo->unused4;
  Data->TimerInfo.EPGMarker             = TimerInfo->EPGMarker;
  Data->TimerInfo.unused5               = TimerInfo->unused5;
  Data->TimerInfo.unknown1              = TimerInfo->unknown1;
  Data->TimerInfo.EventID1              = TimerInfo->EventID1;
  Data->TimerInfo.EventID2              = TimerInfo->EventID2;
  Data->TimerInfo.ServiceIndex          = TimerInfo->ServiceIndex;
  memcpy(Data->TimerInfo.unused8, TimerInfo->unused8, sizeof(Data->TimerInfo.unused8));
  Data->TimerInfo.IceTV                 = TimerInfo->IceTV;
  memcpy(Data->TimerInfo.unused9, TimerInfo->unused9, sizeof(Data->TimerInfo.unused9));

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
  Data->TpInfo.TPMode             = TimerInfo->TpInfo.unused1;
  Data->TpInfo.unused2            = TimerInfo->TpInfo.unused2;
  Data->TpInfo.unused3            = TimerInfo->TpInfo.unused3;
  Data->TpInfo.unused4            = TimerInfo->TpInfo.unused4;

  TRACEEXIT();
  return TRUE;
}

static bool FlashTimerEncode_ST_TMST(TYPE_Timer_TMST *Data, tFlashTimer *TimerInfo)
{
  TRACEENTER();

  memset(Data, 0, sizeof(TYPE_Timer_TMST));

  Data->TimerInfo.TunerIndex            = TimerInfo->TunerIndex;
  Data->TimerInfo.RecMode               = TimerInfo->RecMode;
  Data->TimerInfo.DemuxPath             = TimerInfo->DemuxPath;
  Data->TimerInfo.ManualRec             = TimerInfo->ManualRec;
  Data->TimerInfo.unused1               = TimerInfo->unused1;
  Data->TimerInfo.SatIndex              = TimerInfo->SatIndex;
  Data->TimerInfo.ServiceType           = TimerInfo->ServiceType;
  Data->TimerInfo.ReservationType       = TimerInfo->ReservationType;
  Data->TimerInfo.unused2               = TimerInfo->unused2;
  Data->TimerInfo.ServiceID             = TimerInfo->ServiceID;
  Data->TimerInfo.Duration              = TimerInfo->Duration;
  Data->TimerInfo.unused3               = TimerInfo->unused3;
  strncpy(Data->TimerInfo.FileName, TimerInfo->FileName, 130);
  Data->TimerInfo.StartTime             = TimerInfo->StartTime;
  Data->TimerInfo.EndTime               = TimerInfo->EndTime;
  Data->TimerInfo.PMTPID                = TimerInfo->PMTPID;
  Data->TimerInfo.isRec                 = TimerInfo->isRec;
  Data->TimerInfo.NameSet               = TimerInfo->NameSet;
  Data->TimerInfo.unused4               = TimerInfo->unused4;
  Data->TimerInfo.EPGMarker             = TimerInfo->EPGMarker;
  Data->TimerInfo.unused5               = TimerInfo->unused5;
  Data->TimerInfo.unknown1              = TimerInfo->unknown1;
  Data->TimerInfo.EventID1              = TimerInfo->EventID1;
  Data->TimerInfo.EventID2              = TimerInfo->EventID2;
  Data->TimerInfo.ServiceIndex          = TimerInfo->ServiceIndex;
  memcpy(Data->TimerInfo.unused8, TimerInfo->unused8, sizeof(Data->TimerInfo.unused8));
  Data->TimerInfo.IceTV                 = TimerInfo->IceTV;
  memcpy(Data->TimerInfo.unused9, TimerInfo->unused9, sizeof(Data->TimerInfo.unused9));
  memcpy(Data->unused10, TimerInfo->unused10, sizeof(Data->unused10));

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

  TRACEEXIT();
  return TRUE;
}

static bool FlashTimerEncode_ST_TMST200(TYPE_Timer_TMST200 *Data, tFlashTimer *TimerInfo)
{
  TRACEENTER();

  memset(Data, 0, sizeof(TYPE_Timer_TMST200));

  Data->TimerInfo.TunerIndex            = TimerInfo->TunerIndex;
  Data->TimerInfo.RecMode               = TimerInfo->RecMode;
  Data->TimerInfo.DemuxPath             = TimerInfo->DemuxPath;
  Data->TimerInfo.ManualRec             = TimerInfo->ManualRec;
  Data->TimerInfo.unused1               = TimerInfo->unused1;
  Data->TimerInfo.SatIndex              = TimerInfo->SatIndex;
  Data->TimerInfo.ServiceType           = TimerInfo->ServiceType;
  Data->TimerInfo.ReservationType       = TimerInfo->ReservationType;
  Data->TimerInfo.unused2               = TimerInfo->unused2;
  Data->TimerInfo.ServiceID             = TimerInfo->ServiceID;
  Data->TimerInfo.Duration              = TimerInfo->Duration;
  Data->TimerInfo.unused3               = TimerInfo->unused3;
  strncpy(Data->TimerInfo.FileName, TimerInfo->FileName, 130);
  Data->TimerInfo.StartTime             = TimerInfo->StartTime;
  Data->TimerInfo.EndTime               = TimerInfo->EndTime;
  Data->TimerInfo.PMTPID                = TimerInfo->PMTPID;
  Data->TimerInfo.isRec                 = TimerInfo->isRec;
  Data->TimerInfo.NameSet               = TimerInfo->NameSet;
  Data->TimerInfo.unused4               = TimerInfo->unused4;
  Data->TimerInfo.EPGMarker             = TimerInfo->EPGMarker;
  Data->TimerInfo.unused5               = TimerInfo->unused5;
  Data->TimerInfo.unknown1              = TimerInfo->unknown1;
  Data->TimerInfo.EventID1              = TimerInfo->EventID1;
  Data->TimerInfo.EventID2              = TimerInfo->EventID2;
  Data->TimerInfo.ServiceIndex          = TimerInfo->ServiceIndex;
  memcpy(Data->TimerInfo.unused8, TimerInfo->unused8, sizeof(Data->TimerInfo.unused8));
  Data->TimerInfo.IceTV                 = TimerInfo->IceTV;
  memcpy(Data->TimerInfo.unused9, TimerInfo->unused9, sizeof(Data->TimerInfo.unused9));

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

  TRACEEXIT();
  return TRUE;
}

static bool FlashTimerEncode_ST_TMST360(TYPE_Timer_TMST360 *Data, tFlashTimer *TimerInfo)
{
  TRACEENTER();

  memset(Data, 0, sizeof(TYPE_Timer_TMST360));

  Data->TimerInfo.TunerIndex            = TimerInfo->TunerIndex;
  Data->TimerInfo.RecMode               = TimerInfo->RecMode;
  Data->TimerInfo.DemuxPath             = TimerInfo->DemuxPath;
  Data->TimerInfo.ManualRec             = TimerInfo->ManualRec;
  Data->TimerInfo.unused1               = TimerInfo->unused1;
  Data->TimerInfo.SatIndex              = TimerInfo->SatIndex;
  Data->TimerInfo.ServiceType           = TimerInfo->ServiceType;
  Data->TimerInfo.ReservationType       = TimerInfo->ReservationType;
  Data->TimerInfo.unused2               = TimerInfo->unused2;
  Data->TimerInfo.ServiceID             = TimerInfo->ServiceID;
  Data->TimerInfo.Duration              = TimerInfo->Duration;
  Data->TimerInfo.unused3               = TimerInfo->unused3;
  strncpy(Data->TimerInfo.FileName, TimerInfo->FileName, 130);
  Data->TimerInfo.StartTime             = TimerInfo->StartTime;
  Data->TimerInfo.EndTime               = TimerInfo->EndTime;
  Data->TimerInfo.PMTPID                = TimerInfo->PMTPID;
  Data->TimerInfo.isRec                 = TimerInfo->isRec;
  Data->TimerInfo.NameSet               = TimerInfo->NameSet;
  Data->TimerInfo.unused4               = TimerInfo->unused4;
  Data->TimerInfo.EPGMarker             = TimerInfo->EPGMarker;
  Data->TimerInfo.unused5               = TimerInfo->unused5;
  Data->TimerInfo.unknown1              = TimerInfo->unknown1;
  Data->TimerInfo.EventID1              = TimerInfo->EventID1;
  Data->TimerInfo.EventID2              = TimerInfo->EventID2;
  Data->TimerInfo.ServiceIndex          = TimerInfo->ServiceIndex;
  memcpy(Data->TimerInfo.unused8, TimerInfo->unused8, sizeof(Data->TimerInfo.unused8));
  Data->TimerInfo.IceTV                 = TimerInfo->IceTV;
  memcpy(Data->TimerInfo.unused9, TimerInfo->unused9, sizeof(Data->TimerInfo.unused9));
  memcpy(Data->unused10, TimerInfo->unused10, sizeof(Data->unused10));

  Data->rs_timestamp1         = TimerInfo->rs_timestamp1;

  memcpy(Data->rs_episodeCRID, TimerInfo->rs_episodeCRID, sizeof(TimerInfo->rs_episodeCRID));
  memcpy(Data->rs_seriesCRID, TimerInfo->rs_seriesCRID, sizeof(TimerInfo->rs_episodeCRID));

  Data->rs_unknown1           = TimerInfo->rs_unknown1;
  Data->rs_unknown2           = TimerInfo->rs_unknown2;
  Data->rs_timestamp2         = TimerInfo->rs_timestamp2;
  Data->rs_unknown3           = TimerInfo->rs_unknown3;
  Data->rs_unknown4           = TimerInfo->rs_unknown4;

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

  TRACEEXIT();
  return TRUE;
}

static bool FlashTimerEncode_ST_TMSC(TYPE_Timer_TMSC *Data, tFlashTimer *TimerInfo)
{
  TRACEENTER();

  memset(Data, 0, sizeof(TYPE_Timer_TMSC));

  Data->TimerInfo.TunerIndex            = TimerInfo->TunerIndex;
  Data->TimerInfo.RecMode               = TimerInfo->RecMode;
  Data->TimerInfo.DemuxPath             = TimerInfo->DemuxPath;
  Data->TimerInfo.ManualRec             = TimerInfo->ManualRec;
  Data->TimerInfo.unused1               = TimerInfo->unused1;
  Data->TimerInfo.SatIndex              = TimerInfo->SatIndex;
  Data->TimerInfo.ServiceType           = TimerInfo->ServiceType;
  Data->TimerInfo.ReservationType       = TimerInfo->ReservationType;
  Data->TimerInfo.unused2               = TimerInfo->unused2;
  Data->TimerInfo.ServiceID             = TimerInfo->ServiceID;
  Data->TimerInfo.Duration              = TimerInfo->Duration;
  Data->TimerInfo.unused3               = TimerInfo->unused3;
  strncpy(Data->TimerInfo.FileName, TimerInfo->FileName, 130);
  Data->TimerInfo.StartTime             = TimerInfo->StartTime;
  Data->TimerInfo.EndTime               = TimerInfo->EndTime;
  Data->TimerInfo.PMTPID                = TimerInfo->PMTPID;
  Data->TimerInfo.isRec                 = TimerInfo->isRec;
  Data->TimerInfo.NameSet               = TimerInfo->NameSet;
  Data->TimerInfo.unused4               = TimerInfo->unused4;
  Data->TimerInfo.EPGMarker             = TimerInfo->EPGMarker;
  Data->TimerInfo.unused5               = TimerInfo->unused5;
  Data->TimerInfo.unknown1              = TimerInfo->unknown1;
  Data->TimerInfo.EventID1              = TimerInfo->EventID1;
  Data->TimerInfo.EventID2              = TimerInfo->EventID2;
  Data->TimerInfo.ServiceIndex          = TimerInfo->ServiceIndex;
  memcpy(Data->TimerInfo.unused8, TimerInfo->unused8, sizeof(Data->TimerInfo.unused8));
  Data->TimerInfo.IceTV                 = TimerInfo->IceTV;
  memcpy(Data->TimerInfo.unused9, TimerInfo->unused9, sizeof(Data->TimerInfo.unused9));

  Data->TpInfo.Frequency            = TimerInfo->TpInfo.Frequency;
  Data->TpInfo.SymbolRate           = TimerInfo->TpInfo.SymbolRate;
  Data->TpInfo.TSID                 = TimerInfo->TpInfo.TSID;
  Data->TpInfo.OriginalNetworkID    = TimerInfo->TpInfo.OriginalNetworkID;
  Data->TpInfo.ModulationType       = TimerInfo->TpInfo.Modulation;
  Data->TpInfo.unused1              = TimerInfo->TpInfo.unused1;

  TRACEEXIT();
  return TRUE;
}

bool FlashTimerEncode(void *Data, tFlashTimer *TimerInfo)
{
  bool ret;

  TRACEENTER();

  if(!Data || !TimerInfo)
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
      ret = FlashTimerEncode_ST_TMSS(Data, TimerInfo);
      break;
    }

    case ST_TMST:
    {
      //Depending on the firmware, some Australian machines use the sat structures (200 bytes)
      if(FlashTimerStructSize() == 200)
        ret = FlashTimerEncode_ST_TMST200(Data, TimerInfo);
      else if(FlashTimerStructSize() == 360)
        ret = FlashTimerEncode_ST_TMST360(Data, TimerInfo);
      else
        ret = FlashTimerEncode_ST_TMST(Data, TimerInfo);

      break;
    }

    case ST_TMSC:
    {
      ret = FlashTimerEncode_ST_TMSC(Data, TimerInfo);
      break;
    }

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}


bool FlashTimerSetInfo(int TimerIndex, tFlashTimer *TimerInfo)
{
  TRACEENTER();

  bool ret;

  //TimerIndex out of range
  if((TimerIndex < 0) || (TimerIndex >= TAP_Timer_GetTotalNum()))
  {
    TRACEEXIT();
    return FALSE;
  }

  //TimerInfo is NULL
  if(!TimerInfo)
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
      TYPE_Timer_TMSS  *p;

      p = (TYPE_Timer_TMSS*)(FIS_vFlashBlockTimer());
      if(p)
      {
        p = p + TimerIndex;
        ret = FlashTimerEncode(p, TimerInfo);
      }
      break;
    }

    case ST_TMST:
    {
      //Depending on the firmware, some Australian machines use the sat structures (200 bytes)
      if(FlashTimerStructSize() == 200)
      {
        TYPE_Timer_TMST200  *p;

        p = (TYPE_Timer_TMST200*)(FIS_vFlashBlockTimer());
        if(p)
        {
          p = p + TimerIndex;
          ret = FlashTimerEncode(p, TimerInfo);
        }
        break;
      }
      else if(FlashTimerStructSize() == 360)
      {
        TYPE_Timer_TMST360  *p;

        p = (TYPE_Timer_TMST360*)(FIS_vFlashBlockTimer());
        if(p)
        {
          p = p + TimerIndex;
          ret = FlashTimerEncode(p, TimerInfo);
        }
        break;
      }
      else
      {
        TYPE_Timer_TMST  *p;

        p = (TYPE_Timer_TMST*)(FIS_vFlashBlockTimer());
        if(p)
        {
          p = p + TimerIndex;
          ret = FlashTimerEncode(p, TimerInfo);
        }
        break;
      }
    }

    case ST_TMSC:
    {
      TYPE_Timer_TMSC  *p;

      p = (TYPE_Timer_TMSC*)(FIS_vFlashBlockTimer());
      if(p)
      {
        p = p + TimerIndex;
        ret = FlashTimerEncode(p, TimerInfo);
      }
      break;
    }

    case ST_NRTYPES: break;
  }

  TRACEEXIT();
  return ret;
}
