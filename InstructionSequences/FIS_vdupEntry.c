#include "../libFireBird.h"

inline dword FIS_vdupEntry(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vdupEntry");
  #endif

  static dword          vdupEntry = 0;

  if(!vdupEntry)
    vdupEntry = TryResolve("_dupEntry");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vdupEntry;
}
