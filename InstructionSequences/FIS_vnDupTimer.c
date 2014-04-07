#include "../libFireBird.h"

inline dword FIS_vnDupTimer(void)
{
  TRACEENTER();

  static dword          vnDupTimer = 0;

  if(!vnDupTimer) vnDupTimer = TryResolve("_nDupTimer");

  TRACEEXIT();
  return vnDupTimer;
}
