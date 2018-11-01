#include                <stdio.h>
#include                "libFireBird.h"

void MakeUniqueFileName(char *FileName)
{
  TRACEENTER();

  char                  Path[FBLIB_DIR_SIZE], Name[TS_FILE_NAME_SIZE], Ext[TS_FILE_NAME_SIZE];
  bool                  isRec, isDel;
  int                   fNumber;

  SeparateFileNameComponents(FileName, Path, Name, Ext, &fNumber, &isRec, &isDel);

  if(!fNumber) fNumber = 2;
  TAP_SPrint(FileName, "%s%s%s%s", Path, Name, Ext, isDel ? ".del" : "");
  while(HDD_Exist(FileName))
  {
    TAP_SPrint(FileName, "%s%s-%d%s%s", Path, Name, fNumber++, Ext, isDel ? ".del" : "");
  }

  TRACEEXIT();
}
