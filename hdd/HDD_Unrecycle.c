#include                <stdio.h>
#include                <string.h>
#include                "../libFireBird.h"

bool HDD_Unrecycle(char *FileName)
{
  TRACEENTER();

  char                  Path[FBLIB_DIR_SIZE], Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldName[TS_FILE_NAME_SIZE], NewName[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel, ret;
  int                   fNumber;

  ret = FALSE;
  if(HDD_Exist(FileName))
  {
    SeparateFileNameComponents(FileName, Path, Name, Ext, &fNumber, &isRec, &isDel);

    if(isDel)
    {
      if(fNumber)
        TAP_SPrint(NewName, "%s%s-%d%s", Path, Name, fNumber, Ext);
      else
        TAP_SPrint(NewName, "%s%s%s", Path, Name, Ext);

      TAP_SPrint(OldName, "%s.del", NewName);
      MakeUniqueFileName(NewName);
      if(rename(OldName, NewName) == 0)
      {
        if(isRec && strcmp(Ext, ".nav"))
        {
          OldName[strlen(OldName) - 4] = '\0';
          strcat(OldName, ".inf.del");
          strcat(NewName, ".inf");
          rename(OldName, NewName);

          OldName[strlen(OldName) - 8] = '\0';
          strcat(OldName, ".nav.del");
          NewName[strlen(NewName) - 4] = '\0';
          strcat(NewName, ".nav");
          rename(OldName, NewName);
        }
        ret = TRUE;
      }
    }
  }

  TRACEEXIT();
  return ret;
}
