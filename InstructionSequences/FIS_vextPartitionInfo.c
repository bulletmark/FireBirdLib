#include "../libFireBird.h"

inline dword FIS_vExtPartitionInfo(void)
{
  static dword          vextPartitionInfo = 0;

  if(!vextPartitionInfo) vextPartitionInfo = (dword)TryResolve("_extPartitionInfo");

  return vextPartitionInfo;
}
