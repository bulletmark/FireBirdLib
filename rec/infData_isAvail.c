#include "FBLib_rec.h"

bool infData_isAvail(const char *infFileName, const char *NameTag, dword *PayloadSize)
{
  bool                  ret;

  TRACEENTER();

  ret = FALSE;

  if(infData_OpenFile(infFileName))
    ret = infData_LocateSig(NameTag, PayloadSize);

  infData_CloseFile();

  TRACEEXIT();
  return ret;
}
