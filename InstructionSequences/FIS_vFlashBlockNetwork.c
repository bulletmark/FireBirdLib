#include "../libFireBird.h"

inline dword FIS_vFlashBlockNetwork(void)
{
  static dword          *vFlashNetwork = 0;

  if(!vFlashNetwork)
  {
    vFlashNetwork = (dword*)TryResolve("_network");
    if(!vFlashNetwork) return 0;
  }

  return *vFlashNetwork;
}
