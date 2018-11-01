#include                "FBLib_EPG.h"

dword EPGInfo_GetNrFreeEntries(void)
{
  TRACEENTER();

  dword ret = Appl_GetEvtCountInFreePool();

  TRACEEXIT();
  return ret;
}
