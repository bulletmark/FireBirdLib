#include "../libFireBird.h"

inline dword FIS_vnExtPartition(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vnExtPartition");
  #endif

  static dword          vnExtPartition = 0;

  if(!vnExtPartition) vnExtPartition = (dword)TryResolve("_nExtPartition");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vnExtPartition;
}
