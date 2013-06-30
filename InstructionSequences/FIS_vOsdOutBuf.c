#include "../libFireBird.h"

inline dword FIS_vOsdOutBuf(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vOsdOutBuf");
  #endif

  static dword          vosdOutBuf = 0;

  if(!vosdOutBuf)
    vosdOutBuf = TryResolve("_osdOutBuf");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vosdOutBuf;
}
