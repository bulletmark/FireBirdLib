#include "libFireBird.h"

inline dword FIS_vExtPartitionInfo(void)
{
  TRACEENTER();

  static dword          vextPartitionInfo = 0;

  if(!vextPartitionInfo)
    vextPartitionInfo = (dword)TryResolve("_extPartitionInfo");

  TRACEEXIT();
  return vextPartitionInfo;
}
