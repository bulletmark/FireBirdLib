#include "libFireBird.h"

inline dword FIS_vIsAllPartitionInvalid(void)
{
  TRACEENTER();

  static dword          visAllPartitionInvalid = 0;

  if(!visAllPartitionInvalid)
    visAllPartitionInvalid = (dword)TryResolve("_isAllPartitionInvalid");

  TRACEEXIT();
  return visAllPartitionInvalid;
}
