#include                <stdio.h>
#include                <string.h>
#include                "../libFireBird.h"

void HDD_Rename(char *FileName, char *NewFileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_Rename");
  #endif

  char                  Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  char                  OldInfName[TS_FILE_NAME_SIZE], NewInfName[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;

  if(FileName && NewFileName && NewFileName[0] && TAP_Hdd_Exist(FileName))
  {
    MakeUniqueFileName(NewFileName);
    TAP_Hdd_Rename(FileName, NewFileName);

    SeparateFileNameComponents(FileName, Name, Ext, &fNumber, &isRec, &isDel);
    if(isRec)
    {
      if(fNumber)
        TAP_SPrint(OldInfName, "%s-%d%s.inf%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(OldInfName, "%s%s.inf%s", Name, Ext, isDel ? ".del" : "");

      SeparateFileNameComponents(NewFileName, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewInfName, "%s-%d%s.inf%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(NewInfName, "%s%s.inf%s", Name, Ext, isDel ? ".del" : "");

      TAP_Hdd_Rename(OldInfName, NewInfName);

      SeparateFileNameComponents(FileName, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(OldInfName, "%s-%d%s.nav%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(OldInfName, "%s%s.nav%s", Name, Ext, isDel ? ".del" : "");

      SeparateFileNameComponents(NewFileName, Name, Ext, &fNumber, &isRec, &isDel);
      if(fNumber)
        TAP_SPrint(NewInfName, "%s-%d%s.nav%s", Name, fNumber, Ext, isDel ? ".del" : "");
      else
        TAP_SPrint(NewInfName, "%s%s.nav%s", Name, Ext, isDel ? ".del" : "");

      TAP_Hdd_Rename(OldInfName, NewInfName);
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
