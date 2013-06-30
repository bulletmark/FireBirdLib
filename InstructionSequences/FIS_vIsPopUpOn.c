#include "../libFireBird.h"

inline dword FIS_vIsPopUpOn(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vIsPopUpOn");
  #endif

  static dword          visPopUpOn = 0;

  if(!visPopUpOn)
    visPopUpOn = TryResolve("_isPopUpOn");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return visPopUpOn;
}
