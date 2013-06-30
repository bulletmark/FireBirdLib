#include "../libFireBird.h"

inline dword FIS_vIboxTimerId(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vIboxTimerId");
  #endif

  static byte   *iboxTimerId = NULL;

  if(!iboxTimerId)
    iboxTimerId = (byte*)TryResolve("_iboxTimerId");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (dword)iboxTimerId;
}
