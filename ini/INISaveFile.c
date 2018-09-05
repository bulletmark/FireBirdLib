#include <stdio.h>
#include <string.h>
#include "FBLib_ini.h"
#include "libFireBird.h"

bool INISaveFile(char *FileName, INILOCATION INILocation, char *AppName)
{
  TRACEENTER;

  TYPE_File             *f;
  dword                 ret;

  if(INIBuffer == NULL || INILocation >= INILOCATION_NrENUMs)
  {
    TRACEEXIT;
    return FALSE;
  }

  if(INILocation == INILOCATION_AtAppName && (!AppName || !AppName[0]))
  {
    TRACEEXIT;
    return FALSE;
  }

  if(INILocation < INILOCATION_AtCurrentDir) INILocation = INILOCATION_AtProgramFiles;

  HDD_TAP_PushDir();

  //Make sure that the destination directory exists
  //Nothing to do for INILOCATION_AtCurrentDir
  if(INILocation == INILOCATION_AtProgramFiles || INILocation == INILOCATION_AtSettings || INILocation == INILOCATION_AtAppName)
  {
    if(!HDD_ChangeDir("/ProgramFiles"))
    {
      HDD_TAP_PopDir();

      TRACEEXIT;
      return FALSE;
    }
  }

  if(INILocation == INILOCATION_AtSettings || INILocation == INILOCATION_AtAppName)
  {
    if(!TAP_Hdd_Exist("Settings")) TAP_Hdd_Create("Settings", ATTR_FOLDER);
    if(!HDD_ChangeDir("Settings"))
    {
      HDD_TAP_PopDir();

      TRACEEXIT;
      return FALSE;
    }
  }

  if(INILocation == INILOCATION_AtAppName)
  {
    if(!TAP_Hdd_Exist(AppName)) TAP_Hdd_Create(AppName, ATTR_FOLDER);
    if(!HDD_ChangeDir(AppName))
    {
      HDD_TAP_PopDir();

      TRACEEXIT;
      return FALSE;
    }
  }

  TAP_Hdd_Delete(FileName);
  TAP_Hdd_Create(FileName, ATTR_NORMAL);
  if(!(f = TAP_Hdd_Fopen(FileName)))
  {
    HDD_TAP_PopDir();

    TRACEEXIT;
    return FALSE;
  }

  ret = TAP_Hdd_Fwrite(INIBuffer, strlen(INIBuffer), 1, f);
  TAP_Hdd_Fclose(f);
  HDD_TAP_PopDir();

  TRACEEXIT;
  return (ret == 1);
}
