#include "../libFireBird.h"

inline dword FIS_vApplState(void)
{
  TRACEENTER();

  static dword          vapplState = 0;

  if(!vapplState)
    vapplState = TryResolve("_applState");

  TRACEEXIT();
  return vapplState;
}
