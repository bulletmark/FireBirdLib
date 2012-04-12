#include                <string.h>
#include                "tap.h"
#include                "libFireBird.h"

#define PROGRAM_NAME    "FlashDecode"
#define VERSION         "V0.1"
#define LOGNAME         PROGRAM_NAME".log"
#define FIRMWAREDAT     "FirmwareTMS.dat"

TAP_ID                  (0x8E0A4240);
TAP_PROGRAM_NAME        (PROGRAM_NAME" "VERSION);
TAP_PROGRAM_VERSION     (VERSION);
TAP_AUTHOR_NAME         ("FireBird");
TAP_DESCRIPTION         ("Decodes the contents of the flash memory");
TAP_ETCINFO             (__DATE__);

void PrintLog(char *Text);

char                   *Log = NULL;
dword                   LogSize = 0;
dword                   LogStringSize = 0;
char                    buffer[1024];

#define PRINTLOG(...) {sprintf(buffer, __VA_ARGS__); PrintLog(buffer);}

void PrintLog(char *Text)
{
  LogEntry(LOGNAME, PROGRAM_NAME, TRUE, TIMESTAMP_NONE, Text);
  //TAP_PrintNet("%s\n", Text);
}

dword TAP_EventHandler(word event, dword param1, dword param2)
{
  (void) event;
  (void) param2;

  return param1;
}

char *GetBoolString(bool Flag)
{
  if(Flag)
    return "true";
  else
    return "false";
}

void DumpSystemType(void)
{
  tFWDATHeader         *FWDatHeader;
  tToppyInfo           *ToppyInfo;
  tFWInfo              *FWInfo;
  INILOCATION           Loc;
  SYSTEM_TYPE           SystemType = ST_UNKNOWN;
  char                  x[256];
  int                   i;

  HDD_TAP_PushDir();
  Loc = INILocateFile(FIRMWAREDAT, NULL);
  if (Loc == INILOCATION_NotFound)
  {
    HDD_TAP_PopDir();

    PRINTLOG("%s not found.", FIRMWAREDAT);
  }
  else
  {
    TAP_SPrint(x, "%s found at ", FIRMWAREDAT);
    switch(Loc)
    {
      case INILOCATION_AtCurrentDir:    strcat(x, "current directory"); break;
      case INILOCATION_AtAppName:       strcat(x, "/ProgramFiles/Settings/<appname>"); break;
      case INILOCATION_AtSettings:      strcat(x, "/ProgramFiles/Settings"); break;
      case INILOCATION_AtProgramFiles:  strcat(x, "/ProgramFiles"); break;
      default: strcat(x, "(unhandled)"); break;
    }

    if (!LoadFirmwareDat(&FWDatHeader, &ToppyInfo, &FWInfo))
    {
      HDD_TAP_PopDir();
      PRINTLOG("%s", x);
      PRINTLOG("  Failed while trying to load %s", FIRMWAREDAT);
    }
    else
    {
      HDD_TAP_PopDir();
      PRINTLOG("%s", x);
      PRINTLOG("  Compile date  =  %d-%02d-%02d", FWDatHeader->CompileDate >> 16, (FWDatHeader->CompileDate >> 8) & 0xff, FWDatHeader->CompileDate & 0xff);
      PRINTLOG("  Database      =  %d SysIDs, %d F/W IDs", FWDatHeader->NrOfToppyInfoEntries, FWDatHeader->NrOfFWInfoEntries);
    }

    SystemType = GetSystemType();
    if(ToppyInfo->SystemType == ST_UNKNOWN)
    {
      PRINTLOG("  Your SysID (%d) is not included in %s!", GetSysID(), FIRMWAREDAT);
    }
    else
    {
      for (i = 0; i < (int)FWDatHeader->NrOfToppyInfoEntries; i++, ToppyInfo++)
        if(ToppyInfo->SysID == GetSysID()) break;

      PRINTLOG("  SysID         =  %d", ToppyInfo->SysID);
      PRINTLOG("  Device        =  %s", ToppyInfo->Device);
      PRINTLOG("  AppType       =  %s", ToppyInfo->AppType);

      switch (ToppyInfo->SystemType)
      {
        case ST_UNKNOWN   : break;
        case ST_S         : PRINTLOG("  SystemType    =  ST_S"); break;
        case ST_T         : PRINTLOG("  SystemType    =  ST_T"); break;
        case ST_C         : PRINTLOG("  SystemType    =  ST_C"); break;
        case ST_T5700     : PRINTLOG("  SystemType    =  ST_T5700"); break;
        case ST_TMSS      : PRINTLOG("  SystemType    =  ST_TMSS"); break;
        case ST_TMST      : PRINTLOG("  SystemType    =  ST_TMST"); break;
        case ST_TMSC      : PRINTLOG("  SystemType    =  ST_TMSC"); break;
        case ST_T5800     : PRINTLOG("  SystemType    =  ST_T5800"); break;
        case ST_ST        : PRINTLOG("  SystemType    =  ST_ST"); break;
        case ST_CT        : PRINTLOG("  SystemType    =  ST_CT"); break;
        case ST_TF7k7HDPVR: PRINTLOG("  SystemType    =  ST_TF7k7HDPVR"); break;
        default           : PRINTLOG("  SystemType    =  unhandled");
      }

      switch(ToppyInfo->DisplayType)
      {
        case DT_LED:      PRINTLOG("  DisplayType   =  LED"); break;
        case DT_VFD5500:  PRINTLOG("  DisplayType   =  TF5500 dot matrix VFD"); break;
        case DT_VFDMP:    PRINTLOG("  DisplayType   =  Masterpiece VFD"); break;
      }

      switch(ToppyInfo->RemoteType)
      {
        case RT_5000:     PRINTLOG("  RemoteType    =  5000"); break;
        case RT_2100:     PRINTLOG("  RemoteType    =  2100"); break;
        case RT_7100PLUS: PRINTLOG("  RemoteType    =  7100+"); break;
      }
    }
  }
  PRINTLOG("");
}

void DumpTVServices(void)
{
  int                   ret, i, j;
  tFlashService         Channel;
  char                  s[100];

  ret = FlashServiceGetTotal(SVC_TYPE_Tv);
  PRINTLOG("TV channels (%d)", ret);
  for(i = 0; i < ret; i++)
  {
    if(FlashServiceGetInfo(SVC_TYPE_Tv, i, &Channel))
    {
      PRINTLOG("  %3.3d: '%s' / '%s'", i, Channel.ServiceName, Channel.ProviderName);
      PRINTLOG("    SatIndex=%d, VideoStreamType=%2.2x, AudioStreamType=%2.2x, Tuner=%d, TpIndex=%d, LCN=%d", Channel.SatIndex, Channel.VideoStreamType, Channel.AudioStreamType, Channel.Tuner, Channel.TransponderIndex, Channel.LCN);
      PRINTLOG("    ServiceID=%4.4x, PMTPID=%4.4x, PCRPID=%4.4x, VideoPID=%4.4x, AudioPID=%4.4x", Channel.ServiceID, Channel.PMTPID, Channel.PCRPID, Channel.VideoPID, Channel.AudioPID);
      PRINTLOG("    FlagDelete=%s, FlagCAS=%s, FlagLock=%s, FlagSkip=%s", GetBoolString(Channel.FlagDelete), GetBoolString(Channel.FlagCAS), GetBoolString(Channel.FlagLock), GetBoolString(Channel.FlagSkip));

      s[0] = '\0';
      for(j = 0; j < 6; j++)
      {
        TAP_SPrint(&s[strlen(s)], "%2.2x ", Channel.unknown2[j]);
      }
      PRINTLOG("    unknown1=%4.4x, unknown2=%s", Channel.unknown1, s);
    }
    else
    {
      PRINTLOG("  %3.3d: failed to decode", i);
    }
    PRINTLOG("");
  }
}

void DumpRadioServices(void)
{
  int                   ret, i, j;
  tFlashService         Channel;
  char                  s[100];

  ret = FlashServiceGetTotal(SVC_TYPE_Radio);
  PRINTLOG("Radio channels (%d)", ret);
  for(i = 0; i < ret; i++)
  {
    if(FlashServiceGetInfo(SVC_TYPE_Radio, i, &Channel))
    {
      PRINTLOG("  %3.3d: '%s' / '%s'", i, Channel.ServiceName, Channel.ProviderName);
      PRINTLOG("    SatIndex=%d, VideoStreamType=%2.2x, AudioStreamType=%2.2x, Tuner=%d, TpIndex=%d, LCN=%d", Channel.SatIndex, Channel.VideoStreamType, Channel.AudioStreamType, Channel.Tuner, Channel.TransponderIndex, Channel.LCN);
      PRINTLOG("    ServiceID=%4.4x, PMTPID=%4.4x, PCRPID=%4.4x, VideoPID=%4.4x, AudioPID=%4.4x", Channel.ServiceID, Channel.PMTPID, Channel.PCRPID, Channel.VideoPID, Channel.AudioPID);
      PRINTLOG("    FlagDelete=%s, FlagCAS=%s, FlagLock=%s, FlagSkip=%s", GetBoolString(Channel.FlagDelete), GetBoolString(Channel.FlagCAS), GetBoolString(Channel.FlagLock), GetBoolString(Channel.FlagSkip));

      s[0] = '\0';
      for(j = 0; j < 6; j++)
      {
        TAP_SPrint(&s[strlen(s)], "%2.2x ", Channel.unknown2[j]);
      }
      PRINTLOG("    unknown1=%4.4x, unknown2=%s", Channel.unknown1, s);
    }
    else
    {
      PRINTLOG("  %3.3d: failed to decode", i);
    }
    PRINTLOG("");
  }
}

void DumpSatTables(void)
{
  int                   ret, i, j;
  tFlashSatTable        Sat;
  char                  s[100], t[100];

  ret = FlashSatTablesGetTotal();
  PRINTLOG("Sat tables (%d)", ret);
  for(i = 0; i < ret; i++)
  {
    if(FlashSatTablesGetInfo(i, &Sat))
    {
      PRINTLOG("  %3.3d: '%s'", i, Sat.SatName);
      PRINTLOG("    NrOfTransponders=%d, SatPosition=%d", Sat.NrOfTransponders, Sat.SatPosition);

      switch(GetSystemType())
      {
        case ST_UNKNOWN:
        case ST_S:
        case ST_T:
        case ST_C:
        case ST_T5700:
        case ST_TMST:
        case ST_TMSC:
        case ST_T5800:
        case ST_ST:
        case ST_CT:
        case ST_TF7k7HDPVR:
        case ST_NRTYPES:
          break;

        case ST_TMSS:
        {
          s[0] = '\0';
          for(j = 0; j < 8; j++)
          {
            TAP_SPrint(&s[strlen(s)], "%2.2x ", Sat.unused2[j]);
          }

          t[0] = '\0';
          for(j = 0; j < 22; j++)
          {
            TAP_SPrint(&t[strlen(t)], "%2.2x ", Sat.unknown1[j]);
          }
          PRINTLOG("    unused1=%d, unused2=%s, unknown1=%s", Sat.unused1, s, t);

          PRINTLOG("    LNB1");

          s[0] = '\0';
          for(j = 0; j < 3; j++)
          {
            TAP_SPrint(&s[strlen(s)], "%2.2x ", Sat.LNB[0].DiSEqC12Flags[j]);
          }

          PRINTLOG("      LNBSupply=%d, DiSEqC10=%d, DiSEqC11=%d, DiSEqC12=%d, DiSEqC12Flags=%s", Sat.LNB[0].LNBSupply, Sat.LNB[0].DiSEqC10, Sat.LNB[0].DiSEqC11, Sat.LNB[0].DiSEqC12, s);
          PRINTLOG("      UniversalLNB=%d, Switch22=%d, LowBand=%d, HBFrq=%d, LoopThrough=%d", Sat.LNB[0].UniversalLNB, Sat.LNB[0].Switch22, Sat.LNB[0].LowBand, Sat.LNB[0].HBFrq, Sat.LNB[0].LoopThrough);

          s[0] = '\0';
          for(j = 0; j < 5; j++)
          {
            TAP_SPrint(&s[strlen(s)], "%2.2x ", Sat.LNB[0].unused5[j]);
          }
          PRINTLOG("      unused1=%2.2x, unused2=%2.2x, unused3=%2.2x, unused4=%2.2x, unused5=%s", Sat.LNB[0].unused1, Sat.LNB[0].unused2, Sat.LNB[0].unused3, Sat.LNB[0].unused4, s);

          PRINTLOG("    LNB2");

          s[0] = '\0';
          for(j = 0; j < 3; j++)
          {
            TAP_SPrint(&s[strlen(s)], "%2.2x ", Sat.LNB[1].DiSEqC12Flags[j]);
          }

          PRINTLOG("      LNBSupply=%d, DiSEqC10=%d, DiSEqC11=%d, DiSEqC12=%d, DiSEqC12Flags=%s", Sat.LNB[1].LNBSupply, Sat.LNB[1].DiSEqC10, Sat.LNB[1].DiSEqC11, Sat.LNB[1].DiSEqC12, s);
          PRINTLOG("      UniversalLNB=%d, Switch22=%d, LowBand=%d, HBFrq=%d, LoopThrough=%d", Sat.LNB[1].UniversalLNB, Sat.LNB[1].Switch22, Sat.LNB[1].LowBand, Sat.LNB[1].HBFrq, Sat.LNB[1].LoopThrough);

          s[0] = '\0';
          for(j = 0; j < 5; j++)
          {
            TAP_SPrint(&s[strlen(s)], "%2.2x ", Sat.LNB[1].unused5[j]);
          }
          PRINTLOG("      unused1=%2.2x, unused2=%2.2x, unused3=%2.2x, unused4=%2.2x, unused5=%s", Sat.LNB[1].unused1, Sat.LNB[1].unused2, Sat.LNB[1].unused3, Sat.LNB[1].unused4, s);
          break;
        }
      }
    }
    else
    {
      PRINTLOG("  %3.3d: failed to decode", i);
    }
    PRINTLOG("");
  }
}

void DumpTransponderTable(void)
{
  int                   ret, i, Sat;
  tFlashSatTable        SatTable;
  tFlashTransponderTable TpTable;

  for(Sat = 0; Sat < FlashSatTablesGetTotal(); Sat++)
  {
    FlashSatTablesGetInfo(Sat, &SatTable);
    ret = FlashTransponderTablesGetTotal(Sat);
    PRINTLOG("Transponder tables (%s = %d)", SatTable.SatName, ret);
    for(i = 0; i < ret; i++)
    {
      if(FlashTransponderTablesGetInfo(Sat, i, &TpTable))
      {
        switch(GetSystemType())
        {
          case ST_UNKNOWN:
          case ST_S:
          case ST_T:
          case ST_C:
          case ST_T5700:
          case ST_T5800:
          case ST_ST:
          case ST_CT:
          case ST_TF7k7HDPVR:
          case ST_NRTYPES:
            break;

          case ST_TMSS:
          {
            PRINTLOG("  %3.3d: SatIndex=%d, Frequency=%d, SymbolRate=%d", i, TpTable.SatIndex, TpTable.Frequency, TpTable.SymbolRate);
            PRINTLOG("    TSID=%4.4x, ONID=%4.4x,Pilot=%s", TpTable.TSID, TpTable.OriginalNetworkID, GetBoolString(TpTable.Pilot));
            PRINTLOG("    FEC=%d, Modulation=%d, ModSystem=%d, Polarisation=%d, ClockSync=%s", TpTable.FEC, TpTable.Modulation, TpTable.ModSystem, TpTable.Polarisation, GetBoolString(TpTable.ClockSync));
            PRINTLOG("    unused1=%4.4x, unused2=%4.4x, unused3=%2.2x, unused4=%4.4x", TpTable.unused1, TpTable.unused2, TpTable.unused3, TpTable.unused4);
            break;
          }

          case ST_TMST:
          {
            PRINTLOG("  %3.3d: SatIndex=%d, Frequency=%d", i, TpTable.SatIndex, TpTable.Frequency);
            PRINTLOG("    ChannelNr=%d, Bandwidth=%d, TSID=%4.4x, ONID=%4.4x, NetworkID=%4.4x, LPHP=%d", TpTable.ChannelNr, TpTable.Bandwidth, TpTable.TSID, TpTable.OriginalNetworkID, TpTable.NetworkID, TpTable.LPHP);
            PRINTLOG("    unused1=%4.4x, unused2=%4.4x", TpTable.unused1, TpTable.unused2);
            break;
          }

          case ST_TMSC:
          {
            PRINTLOG("  %3.3d: SatIndex=%d, Frequency=%d, SymbolRate=%d", i, TpTable.SatIndex, TpTable.Frequency, TpTable.SymbolRate);
            PRINTLOG("    TSID=%4.4x, ONID=%4.4x, Modulation=%d", TpTable.TSID, TpTable.OriginalNetworkID, TpTable.Modulation);
            PRINTLOG("    unused1=%4.4x", TpTable.unused1);
            break;
          }
        }
      }
      else
      {
        PRINTLOG("  %3.3d: failed to decode", i);
      }
      PRINTLOG("");
    }
  }
}

void DumpTimeInfo(void)
{
  tFlashTimeInfo        TimeInfo;

  PRINTLOG("Time info");
  if(FlashTimeGetInfo(&TimeInfo))
  {
    PRINTLOG("  UTCOffset=%d, SleepTimer=%d, GMTCollection=%d, Mode=%d, DST=%2.2x", TimeInfo.UTCOffset, TimeInfo.SleepTimer, TimeInfo.GMTCollection, TimeInfo.Mode, TimeInfo.DST);
    PRINTLOG("  unknown1=%2.2x, unknown2=%2.2x, unknown3=%2.2x, unknown4=%2.2x, unknown5=%2.2x", TimeInfo.unknown1, TimeInfo.unknown2, TimeInfo.unknown3, TimeInfo.unknown4, TimeInfo.unknown5);
  }
  else
  {
    PRINTLOG("  failed to decode");
  }
  PRINTLOG("");
}

void DumpTimer(void)
{
  int                   ret, i, j;
  tFlashTimer           TimerInfo;
  char                  s[100], t[100];

  ret = TAP_Timer_GetTotalNum();
  PRINTLOG("Timer (%d)", ret);
  for(i = 0; i < ret; i++)
  {
    if(FlashTimerGetInfo(i, &TimerInfo))
    {
      PRINTLOG("  %3.3d: '%s'", i, TimerInfo.FileName);
      PRINTLOG("    TunerIndex=%d, RecMode=%d, DemuxPath=%d, ManualRec=%d, SatIndex=%d, ServiceType=%d, PMT=%4.4x", TimerInfo.TunerIndex, TimerInfo.RecMode, TimerInfo.DemuxPath, TimerInfo.ManualRec, TimerInfo.SatIndex, TimerInfo.ServiceType, TimerInfo.PMTPID);
      PRINTLOG("    ReservationType=%d, ServiceID=%4.4x, Duration=%d, StartTime=%4.4x, EndTime=%4.4x", TimerInfo.ReservationType, TimerInfo.ServiceID, TimerInfo.Duration, TimerInfo.StartTime, TimerInfo.EndTime);
      PRINTLOG("    isRec=%d, NameSet=%d, EPGMarker=%d, EventID1=%4.4x, EventID2=%4.4x, ServiceIndex=%d", TimerInfo.isRec, TimerInfo.NameSet, TimerInfo.EPGMarker, TimerInfo.EventID1, TimerInfo.EventID2, TimerInfo.ServiceIndex);

      s[0] = '\0';
      for(j = 0; j < 6; j++)
      {
        TAP_SPrint(&s[strlen(s)], "%2.2x ", TimerInfo.unused5[j]);
      }
      t[0] = '\0';
      for(j = 0; j < 14; j++)
      {
        TAP_SPrint(&t[strlen(t)], "%2.2x ", TimerInfo.unused8[j]);
      }


      PRINTLOG("    unused1=%2.2x, unused2=%2.2x, unused3=%2.2x, unused5=%s, unused6=%4.4x, unused7=%4.4x, unused8=%s", TimerInfo.unused1, TimerInfo.unused2, TimerInfo.unused3, s, TimerInfo.unused6, TimerInfo.unused7, t);
    }
    else
    {
      PRINTLOG("  %3.3d: failed to decode", i);
    }
    PRINTLOG("");
  }
}

void DumpADTimer(void)
{
  int                   i;
  tAutoDescrambleTimer  ADTimer;

  PRINTLOG("AutoDescramble timer");
  if(FlashADGetInfo(&ADTimer))
  {
    PRINTLOG("  StartTime=%4.4x, EndTime=%4.4x, Duration=%d, ReservationType=%d, DelOrig=%s, NrOfFiles=%d, TotalTime=%d", ADTimer.StartTime, ADTimer.EndTime, ADTimer.Duration, ADTimer.ReservationType, GetBoolString(ADTimer.DelOrig), ADTimer.NrOfFiles, ADTimer.TotalTime);
    PRINTLOG("  unknown1=%4.4x, unknown2=%4.4x, unknown3=%4.4x", ADTimer.unknown1, ADTimer.unknown2, ADTimer.unknown3);

    for(i = 0; i < ADTimer.NrOfFiles; i++)
    {
      PRINTLOG("   %3.3d: %s", i, ADTimer.FileName[i]);
    }
  }
  else
  {
    PRINTLOG("  failed to decode");
  }
  PRINTLOG("");
}

int TAP_Main(void)
{
  DumpSystemType();
  DumpTVServices();
  DumpRadioServices();
  DumpSatTables();
  DumpTransponderTable();
  DumpTimeInfo();
  DumpTimer();
  DumpADTimer();

  return 0;
}
