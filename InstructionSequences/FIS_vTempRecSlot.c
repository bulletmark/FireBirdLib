#include "../libFireBird.h"

inline dword FIS_vTempRecSlot(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vTempRecSlot");
  #endif

  static dword          vTempRecSlot = 0;

  if(!vTempRecSlot)
    vTempRecSlot = TryResolve("_tempRecSlot");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vTempRecSlot;
}
