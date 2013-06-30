#include                <stdio.h>
#include                <string.h>
#include                "../libFireBird.h"

void HDD_Unrecycle(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_Unrecycle");
  #endif

  char                  Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldName[TS_FILE_NAME_SIZE], NewName[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;

  if(TAP_Hdd_Exist(FileName))
  {
    SeparateFileNameComponents(FileName, Name, Ext, &fNumber, &isRec, &isDel);

    if(isDel)
    {
      if(fNumber)
        TAP_SPrint(NewName, "%s-%d%s", Name, fNumber, Ext);
      else
        TAP_SPrint(NewName, "%s%s", Name, Ext);

      TAP_SPrint(OldName, "%s.del", NewName);
      MakeUniqueFileName(NewName);
      TAP_Hdd_Rename(OldName, NewName);

      if(isRec && strcmp(Ext, ".nav"))
      {
        OldName[strlen(OldName) - 4] = '\0';
        strcat(OldName, ".inf.del");
        strcat(NewName, ".inf");
        TAP_Hdd_Rename(OldName, NewName);

        OldName[strlen(OldName) - 8] = '\0';
        strcat(OldName, ".nav.del");
        NewName[strlen(NewName) - 4] = '\0';
        strcat(NewName, ".nav");
        TAP_Hdd_Rename(OldName, NewName);
      }
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
