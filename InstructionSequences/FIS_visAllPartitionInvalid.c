#include "../libFireBird.h"

inline dword FIS_vIsAllPartitionInvalid(void)
{
  static dword          visAllPartitionInvalid = 0;

  if(!visAllPartitionInvalid) visAllPartitionInvalid = (dword)TryResolve("_isAllPartitionInvalid");

  return visAllPartitionInvalid;
}
