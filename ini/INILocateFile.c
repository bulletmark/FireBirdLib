#include                <string.h>
#include                "libFireBird.h"

//Attention: this function will stay in the directory where it has found the file
//It is up to the caller to use HDD_TAP_PushDir() and HDD_TAP_PopDir()

INILOCATION INILocateFile(char *FileName, char *AppName)
{
  TRACEENTER();

  INILOCATION           location = INILOCATION_NotFound;
  char                  dir[200] = "";

  if(FileName)
  {
    //Current directory?
    if(TAP_Hdd_Exist(FileName)) location = INILOCATION_AtCurrentDir;
    //Else search (which automatically activates tapapifix)
    else
    {
      HDD_TAP_GetCurrentDir(dir);

      if(HDD_ChangeDir("/ProgramFiles"))
      {
        //Try /ProgramFiles
        if(TAP_Hdd_Exist(FileName))
        {
          location = INILOCATION_AtProgramFiles;
          strcpy(dir, "/ProgramFiles");
        }

        if(HDD_ChangeDir("Settings"))
        {
          //Try /ProgramFiles/Settings
          if(TAP_Hdd_Exist(FileName))
          {
            location = INILOCATION_AtSettings;
            strcpy(dir, "/ProgramFiles/Settings");
          }

          //Try /ProgramFiles/Settings/<AppName>
          if(AppName && *AppName && (*AppName != '/') && HDD_ChangeDir(AppName) && TAP_Hdd_Exist(FileName))
          {
            location = INILOCATION_AtAppName;
            dir[0] = '\0';
          }
        }
      }
    }
  }

  //Restore the directory where the file has been found
  if(*dir) HDD_ChangeDir(dir);

  TRACEEXIT();
  return location;
}
