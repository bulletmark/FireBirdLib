#include "../libFireBird.h"

inline dword FIS_vFlashBlockServerData(void)
{
  static dword          *vFlashServerData = 0;

  if(!vFlashServerData)
  {
    vFlashServerData = (dword*)TryResolve("_serverData");
    if(!vFlashServerData) return 0;
  }

  return *vFlashServerData;
}

