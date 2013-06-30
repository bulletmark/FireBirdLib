#include "../libFireBird.h"

inline dword FIS_vBootReason(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vBootReason");
  #endif

  static dword          vBootReason = 0;

  if(!vBootReason)
    vBootReason = TryResolve("_powerOnSrc");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vBootReason;
}
