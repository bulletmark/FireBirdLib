#include "libFireBird.h"

dword HDD_TAP_GetIDByFileName(const char *TAPFileName)
{
  TRACEENTER();

  tTAPInfo              pTAPInfo;

  if(HDD_TAP_GetInfo(TAPFileName, &pTAPInfo))
  {
    TRACEEXIT();
    return pTAPInfo.TAPID;
  }

  TRACEEXIT();
  return 0;
}
