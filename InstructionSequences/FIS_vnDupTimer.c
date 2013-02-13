#include "../libFireBird.h"

inline dword FIS_vnDupTimer(void)
{
  static dword          vnDupTimer = 0;

  if(!vnDupTimer) vnDupTimer = TryResolve("_nDupTimer");
  return (dword)vnDupTimer;
}
