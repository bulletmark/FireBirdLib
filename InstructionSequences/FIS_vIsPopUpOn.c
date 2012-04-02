#include "../libFireBird.h"

inline dword FIS_vIsPopUpOn(void)
{
  static dword          visPopUpOn = 0;

  if (!visPopUpOn)
    visPopUpOn = TryResolve("_isPopUpOn");

  return visPopUpOn;
}
