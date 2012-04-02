#include "../libFireBird.h"

inline dword FIS_vApplState(void)
{
  static dword          vapplState = 0;

  if (!vapplState)
    vapplState = TryResolve("_applState");

  return vapplState;
}
