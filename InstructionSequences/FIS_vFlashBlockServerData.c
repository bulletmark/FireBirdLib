#include "../libFireBird.h"

inline dword FIS_vFlashBlockServerData(void)
{
  TRACEENTER();

  static dword          *vFlashServerData = 0;

  if(!vFlashServerData)
    vFlashServerData = (dword*)TryResolve("_serverData");

  TRACEEXIT();
  return (vFlashServerData ? *vFlashServerData : 0);
}

