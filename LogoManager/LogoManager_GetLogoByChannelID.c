#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

TYPE_GrData *LogoManager_GetLogoByChannelID(ulong64 ChannelID, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("LogoManager_GetLogoByChannelID");
  #endif

  int                   i;
  TYPE_File            *f;
  char                  s[20], LogoName[40];
  TYPE_GrData          *GrData;

  LogoManager_Initialize(LogoManager_CB);

  for(i = 0; i < LogoManager_NrLogos; i++)
  {
    if(LogoManager_LogoData[i].ChannelID == ChannelID &&
       LogoManager_LogoData[i].Style  == LogoStyle &&
       LogoManager_LogoData[i].Size   == LogoSize &&
       LogoManager_LogoData[i].Aspect == LogoAR)
    {
      if(!LogoManager_LogoData[i].grData)
      {
        //The graphics data is not yet available in memory. Load it
        LogoManager_LogoData[i].grData = TAP_MemAlloc(LogoManager_LogoData[i].grDataSize);
        if(!LogoManager_LogoData[i].grData)
        {
          #ifdef DEBUG_FIREBIRDLIB
            CallTraceExit(NULL);
          #endif

          return NULL;
        }

        HDD_TAP_PushDir();
        HDD_ChangeDir(LOGOROOT);
        f = TAP_Hdd_Fopen(LOGOCACHE);
        if(f)
        {
          TAP_Hdd_Fseek(f, LogoManager_LogoData[i].CachePosition, SEEK_SET);
          TAP_Hdd_Fread(LogoManager_LogoData[i].grData, LogoManager_LogoData[i].grDataSize, 1, f);
          TAP_Hdd_Fclose(f);
          LogoManager_LogoData[i].grData->data = (byte*)LogoManager_LogoData[i].grData + sizeof(TYPE_GrData);
        }
        HDD_TAP_PopDir();
      }

      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return LogoManager_LogoData[i].grData;
    }
  }

  //No hit, try to translate the channel ID into a name via the LIL
  HDD_TAP_PushDir();
  HDD_ChangeDir(LOGOROOT);
  if(TAP_Hdd_Exist(LILNAME))
  {
    TAP_SPrint(s, "%16.16llx", ChannelID);
    INIOpenFile(LILNAME, NULL);
    INIGetString(s, LogoName, "", 40);
    INICloseFile();
    if(LogoName[0])
    {
      HDD_TAP_PopDir();
      GrData = LogoManager_GetLogoByLogoName(LogoName, LogoStyle, LogoSize, LogoAR);

      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return GrData;
    }
  }
  HDD_TAP_PopDir();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return NULL;
}
