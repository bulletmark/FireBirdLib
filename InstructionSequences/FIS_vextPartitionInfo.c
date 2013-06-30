#include "../libFireBird.h"

inline dword FIS_vExtPartitionInfo(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vExtPartitionInfo");
  #endif

  static dword          vextPartitionInfo = 0;

  if(!vextPartitionInfo)
    vextPartitionInfo = (dword)TryResolve("_extPartitionInfo");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vextPartitionInfo;
}
