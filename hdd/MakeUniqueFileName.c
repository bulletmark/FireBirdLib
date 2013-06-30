#include                <stdio.h>
#include                "../libFireBird.h"

void MakeUniqueFileName(char *FileName)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("MakeUniqueFileName");
  #endif

  char                  Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;

  SeparateFileNameComponents(FileName, Name, Ext, &fNumber, &isRec, &isDel);

  if(!fNumber) fNumber = 2;
  TAP_SPrint(FileName, "%s%s%s", Name, Ext, isDel ? ".del" : "");
  while(TAP_Hdd_Exist(FileName))
  {
    TAP_SPrint(FileName, "%s-%d%s%s", Name, fNumber++, Ext, isDel ? ".del" : "");
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
