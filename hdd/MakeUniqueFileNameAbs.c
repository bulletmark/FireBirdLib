#include                <stdio.h>
#include                "FBLib_hdd.h"
#include                "../libFireBird.h"

void MakeUniqueFileNameAbs(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("MakeUniqueFileNameAbs");
  #endif

  char                  Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;
  tstat64               statbuf;

  SeparateFileNameComponents(FileName, Name, Ext, &fNumber, &isRec, &isDel);

  if(!fNumber) fNumber = 2;
  TAP_SPrint(FileName, "%s%s%s", Name, Ext, isDel ? ".del" : "");

  while(stat64(FileName, &statbuf) == 0)
  {
    TAP_SPrint(FileName, "%s-%d%s%s", Name, fNumber++, Ext, isDel ? ".del" : "");
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
