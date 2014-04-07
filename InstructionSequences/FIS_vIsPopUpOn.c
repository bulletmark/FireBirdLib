#include "../libFireBird.h"

inline dword FIS_vIsPopUpOn(void)
{
  TRACEENTER();

  static dword          visPopUpOn = 0;

  if(!visPopUpOn)
    visPopUpOn = TryResolve("_isPopUpOn");

  TRACEEXIT();
  return visPopUpOn;
}
