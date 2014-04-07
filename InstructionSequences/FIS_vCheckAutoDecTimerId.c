#include "../libFireBird.h"

inline dword FIS_vCheckAutoDecTimerId(void)
{
  TRACEENTER();

  static dword          _checkAutoDecTimerId = 0;

  if(!_checkAutoDecTimerId)
    _checkAutoDecTimerId = TryResolve("_checkAutoDecTimerId");

  TRACEEXIT();
  return _checkAutoDecTimerId;
}
