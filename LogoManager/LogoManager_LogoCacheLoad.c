#include                <string.h>
#include                <stdlib.h>
#include                "../libFireBird.h"
#include                "FBLib_LogoManager.h"

bool LogoManager_LogoCacheLoad(void)
{
  bool                  Result = FALSE;
  char                  ID[4];
  dword                 Version;
  TYPE_File            *f;
  int                   i;

  HDD_TAP_PushDir();
  HDD_ChangeDir(LOGOROOT);

  if(!TAP_Hdd_Exist(LOGOCACHE)) LogoManager_LogoCacheRebuild();

  if(TAP_Hdd_Exist(LOGOCACHE))
  {
    f = TAP_Hdd_Fopen(LOGOCACHE);
    if(f)
    {
      TAP_Hdd_Fread(ID, 4, 1, f);
      TAP_Hdd_Fread(&Version, 4, 1, f);
      if((strcmp(ID, LOGOCACHEID) == 0) && (Version == LOGOCACHEVERSION))
      {
        TAP_Hdd_Fread(&LogoManager_NrLogos, sizeof(dword), 1, f);
        if(LogoManager_NrLogos)
        {
          if(LogoManager_LogoData) TAP_MemFree(LogoManager_LogoData);
          LogoManager_LogoData = TAP_MemAlloc(LogoManager_NrLogos * sizeof(tLogoData));
          if(!LogoManager_LogoData)
          {
            if(LogoManager_CB) LogoManager_CB(-1, 0);
            HDD_TAP_PopDir();
            return FALSE;
          }
          TAP_Hdd_Fread(LogoManager_LogoData, sizeof(tLogoData), LogoManager_NrLogos, f);
          for(i = 0; i < LogoManager_NrLogos; i++)
            LogoManager_LogoData[i].grData = NULL;
        }
        TAP_Hdd_Fclose(f);
        if(LogoManager_CB) LogoManager_CB(0, LogoManager_NrLogos);
        Result = TRUE;
      }
      else
      {
        if(LogoManager_CB) LogoManager_CB(-1, 1);
        TAP_Hdd_Fclose(f);
        TAP_Hdd_Delete(LOGOCACHE);
      }
    }
  }
  HDD_TAP_PopDir();

  return Result;
}
