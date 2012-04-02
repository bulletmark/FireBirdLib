#include "../libFireBird.h"

inline dword FIS_vCheckAutoDecTimerId(void)
{
  static dword          _checkAutoDecTimerId = 0;

  if(!_checkAutoDecTimerId)
  {
    _checkAutoDecTimerId = TryResolve("_checkAutoDecTimerId");
  }

  return _checkAutoDecTimerId;
}
