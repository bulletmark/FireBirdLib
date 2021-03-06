#include                <stdio.h>
#include                <string.h>
#include                <stdlib.h>
#include                "libFireBird.h"
#include                "FBLib_LogoManager.h"

tLogoData              *LogoManager_LogoData = NULL;
int                     LogoManager_NrLogos = 0;
bool                    LogoManager_LUTInitialized = FALSE;

void (*LogoManager_CB)(int CallbackType, int Param1) = NULL;

void LogoManager_Initialize(void *CallbackRoutine)
{
  TRACEENTER();

  char                  cmd[255];
  TYPE_FolderEntry      FolderEntry;
  int                   NrFiles, i;

  LogoManager_CB = CallbackRoutine;

  HDD_TAP_PushDir();
  HDD_ChangeDir(DIR_PROGRAMFILES);
  if(!TAP_Hdd_Exist(DIR_SETTINGS)) TAP_Hdd_Create(DIR_SETTINGS, ATTR_FOLDER);
  if(!TAP_Hdd_Exist(DIR_LOGOS)) HDD_ChangeDir(DIR_SETTINGS);
  if(!TAP_Hdd_Exist(DIR_LOGOS)) TAP_Hdd_Create(DIR_LOGOS, ATTR_FOLDER);
  HDD_ChangeDir(LOGOROOT);

  if(!LogoManager_LUTInitialized || !TAP_Hdd_Exist(LOGOCACHE))
  {
    LogoManager_MoveExternalUpdates();

    //Check if there's a packed logo file, unpack and erase the tar
    if(TAP_Hdd_Exist(LOGOPACK))
    {
      if(LogoManager_CB) LogoManager_CB(1, 0);
      TAP_SPrint(cmd, "cd %s%s; %s/ProgramFiles/busybox tar xf %s", TAPFSROOT, LOGOROOT, TAPFSROOT, LOGOPACK);
      system(cmd);
      TAP_Hdd_Delete(LOGOPACK);
      TAP_Hdd_Delete(LOGOCACHE);
    }

    if(!TAP_Hdd_Exist(LILNAME))
      LogoManager_UpdateLIL();

    //Check if there are lil updates
    NrFiles = TAP_Hdd_FindFirst(&FolderEntry, "add");
    for(i = 0; i < NrFiles; i++)
    {
      if(FolderEntry.attr == ATTR_NORMAL)
      {
        if(LogoManager_CB) LogoManager_CB(1, 0);
        LogoManager_ProcessLILAdd(FolderEntry.name);
        TAP_Hdd_Delete(FolderEntry.name);
        TAP_Hdd_Delete(LOGOCACHE);
      }

      TAP_Hdd_FindNext(&FolderEntry);
    }

    //Check if the cache file already exists
    LogoManager_LogoCacheLoad();
    LogoManager_LUTInitialized = TRUE;
  }

  HDD_TAP_PopDir();

  TRACEEXIT();
}
