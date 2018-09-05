#include                <string.h>
#include                <stdlib.h>
#include                "libFireBird.h"
#include                "FBLib_LogoManager.h"

void LogoManager_ProcessLILAdd(char *AddFileName)
{
  TRACEENTER;

  TYPE_File            *f;
  int                   fs;
  char                 *Text, Line[80];

  HDD_TAP_PushDir();
  HDD_ChangeDir(LOGOROOT);
  INIOpenFile(LILNAME, NULL);

  f = TAP_Hdd_Fopen(AddFileName);
  if(f)
  {
    fs = TAP_Hdd_Flen(f);
    Text = TAP_MemAlloc(fs+1);
    if(Text)
    {
      TAP_Hdd_Fread(Text, 1, fs, f);
      Text[fs] = '\0';

      while(*Text)
      {
        ExtractLine(Text, Line);
        if(Line[0] == '0' && Line[1] == 'x' && Line[18] == '=')
        {
          LowerCase(Line);
          Line[18] = '\0';
          INISetString(&Line[2], &Line[19]);
        }
      }
      TAP_MemFree(Text);
    }
    TAP_Hdd_Fclose(f);
  }

  INISaveFile(LILNAME, INILOCATION_AtCurrentDir, NULL);
  INICloseFile();
  HDD_TAP_PopDir();

  TRACEEXIT;
}
