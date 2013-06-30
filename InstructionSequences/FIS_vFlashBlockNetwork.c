#include "../libFireBird.h"

inline dword FIS_vFlashBlockNetwork(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vFlashBlockNetwork");
  #endif

  static dword          *vFlashNetwork = 0;

  if(!vFlashNetwork)
   vFlashNetwork = (dword*)TryResolve("_network");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (vFlashNetwork ? *vFlashNetwork : 0);
}
