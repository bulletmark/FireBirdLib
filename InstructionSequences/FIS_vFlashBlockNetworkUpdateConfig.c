#include "../libFireBird.h"

inline dword FIS_vFlashBlockNetworkUpdateConfig(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockNetworkUpdateConfig");
  #endif

  static dword          *vFlashNetworkUpdateConfig = 0;

  if(!vFlashNetworkUpdateConfig)
    vFlashNetworkUpdateConfig = (dword*)TryResolve("_networkUpdateConfig");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashNetworkUpdateConfig ? *vFlashNetworkUpdateConfig : 0);
}
