#include "libFireBird.h"

inline dword FIS_vFlashBlockNetworkUpdateConfig(void)
{
  TRACEENTER();

  static dword          *vFlashNetworkUpdateConfig = 0;

  if(!vFlashNetworkUpdateConfig)
    vFlashNetworkUpdateConfig = (dword*)TryResolve("_networkUpdateConfig");

  TRACEEXIT();
  return (vFlashNetworkUpdateConfig ? *vFlashNetworkUpdateConfig : 0);
}
