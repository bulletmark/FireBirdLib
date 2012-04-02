#include "../libFireBird.h"

inline dword FIS_vnExtPartition(void)
{
  static dword          vnExtPartition = 0;

  if(!vnExtPartition) vnExtPartition = (dword)TryResolve("_nExtPartition");

  return vnExtPartition;
}
