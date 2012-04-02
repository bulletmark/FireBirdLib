#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

TYPE_GrData *LogoManager_GetLogoByLogoName(char *LogoName, tLogoStyle LogoStyle, tLogoSize LogoSize, tLogoAspect LogoAR)
{
  int                   i;
  TYPE_File            *f;

  LogoManager_Initialize(LogoManager_CB);

  for(i = 0; i < LogoManager_NrLogos; i++)
  {
    if(LogoManager_LogoData[i].Style  == LogoStyle &&
       LogoManager_LogoData[i].Size   == LogoSize &&
       LogoManager_LogoData[i].Aspect == LogoAR &&
       !strcmp(LogoManager_LogoData[i].LogoName, LogoName))
    {
      if(!LogoManager_LogoData[i].grData)
      {
        //The graphics data is not yet available in memory. Load it
        LogoManager_LogoData[i].grData = TAP_MemAlloc(LogoManager_LogoData[i].grDataSize);
        if(!LogoManager_LogoData[i].grData) return NULL;

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
      return LogoManager_LogoData[i].grData;
    }
  }
  return NULL;
}
