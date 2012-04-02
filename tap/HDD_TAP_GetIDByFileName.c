#include "../libFireBird.h"

dword HDD_TAP_GetIDByFileName (char *TAPFileName)
{
   tTAPInfo             pTAPInfo;

  if(HDD_TAP_GetInfo(TAPFileName, &pTAPInfo))
    return pTAPInfo.TAPID;
  else
    return 0;
}
