#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

int LogoManager_UpdateLIL(void)
{
  TRACEENTER();

  typedef struct
  {
    ulong64             ChannelID;
    char                Name[MAXLOGONAME+1];
  }tNewIDs;

  int                   nTvSvc, nRadioSvc;
  int                   i;
  TYPE_TapChInfo        chInfo;
  char                  s[255], LogoName[MAX_SvcName + 1];
  SYSTEM_TYPE           SystemType;
  tFlashSatTable        SatInfo;

  word                  SatPos;
  ulong64               ChannelID;
  tNewIDs              *NewIDs;
  int                   NewIDCount;

  SystemType = GetSystemType();

  HDD_TAP_PushDir();
  HDD_ChangeDir(LOGOROOT);

  TAP_Channel_GetTotalNum(&nTvSvc, &nRadioSvc);
  NewIDs = TAP_MemAlloc((nTvSvc + nRadioSvc) * sizeof(tNewIDs));
  NewIDCount = 0;

  INIOpenFile(LILNAME, NULL);

  for(i = 0; i < nTvSvc; i++)
  {
    TAP_Channel_GetInfo(SVC_TYPE_Tv, i, &chInfo);
    FlashSatTablesGetInfo(chInfo.satIdx, &SatInfo);

    switch(SystemType)
    {
      case ST_S:
      case ST_TMSS:
      {
        SatPos = SatInfo.SatPosition;
        break;
      }

      default:
        SatPos = 0;
        break;
    }

    ChannelID = LogoManager_CalculateChannelID(SatPos, chInfo.orgNetId, chInfo.tsId, chInfo.svcId);
    TAP_SPrint(s, "%16.16llx", ChannelID);
    if(!INIKeyExists(s))
    {
      NewIDs[NewIDCount].ChannelID = ChannelID;
      strcpy(NewIDs[NewIDCount].Name, LogoManager_ChannelNameToLogoName(chInfo.chName, LogoName, sizeof(LogoName)));
      if(NewIDs[NewIDCount].Name[0]) NewIDCount++;
    }
  }

  for(i = 0; i < nRadioSvc; i++)
  {
    TAP_Channel_GetInfo(SVC_TYPE_Radio, i, &chInfo);
    FlashSatTablesGetInfo(chInfo.satIdx, &SatInfo);

    switch(SystemType)
    {
      case ST_S:
      case ST_TMSS:
      {
        SatPos = SatInfo.SatPosition;
        break;
      }

      default:
        SatPos = 0;
        break;
    }

    ChannelID = LogoManager_CalculateChannelID(SatPos, chInfo.orgNetId, chInfo.tsId, chInfo.svcId);
    TAP_SPrint(s, "%16.16llx", ChannelID);
    if(!INIKeyExists(s))
    {
      NewIDs[NewIDCount].ChannelID = ChannelID;
      TAP_SPrint(NewIDs[NewIDCount].Name, "r_%s", LogoManager_ChannelNameToLogoName(chInfo.chName, LogoName, sizeof(LogoName)));
      if(NewIDs[NewIDCount].Name[0]) NewIDCount++;
    }
  }

  INICloseFile();

  if(NewIDCount > 0)
  {
    TYPE_File          *f;
    word                year;
    byte                month, day, weekDay;

    if(!TAP_Hdd_Exist(LILNAME)) TAP_Hdd_Create(LILNAME, ATTR_NORMAL);
    f = TAP_Hdd_Fopen(LILNAME);

    if(!f)
    {
      HDD_TAP_PopDir();
      if(LogoManager_CB) LogoManager_CB(-1, 3);

      TRACEEXIT();
      return -1;
    }

    TAP_Hdd_Fseek(f, 0, SEEK_END);
    TAP_ExtractMjd(Now(NULL) >> 16, &year, &month, &day, &weekDay);
    TAP_SPrint(s, "\n\n# Added %4.4d-%2.2d-%2.2d\n", year, month, day);
    TAP_Hdd_Fwrite(s, 1, strlen(s), f);

    for(i = 0; i < NewIDCount; i++)
    {
      TAP_SPrint(s, "%16.16llx=%s\n", NewIDs[i].ChannelID, NewIDs[i].Name);
      TAP_Hdd_Fwrite(s, 1, strlen(s), f);
    }
    TAP_Hdd_Fclose(f);
    if(LogoManager_CB) LogoManager_CB(5, NewIDCount);

  }

  TAP_MemFree(NewIDs);

  HDD_TAP_PopDir();

  TRACEEXIT();
  return NewIDCount;
}
