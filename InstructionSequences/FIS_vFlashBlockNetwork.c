#include "libFireBird.h"

inline dword FIS_vFlashBlockNetwork(void)
{
  TRACEENTER();

  static dword          *vFlashNetwork = 0;

  if(!vFlashNetwork)
   vFlashNetwork = (dword*)TryResolve("_network");

  TRACEEXIT();
  return (vFlashNetwork ? *vFlashNetwork : 0);
}
