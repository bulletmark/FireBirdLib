#include "libFireBird.h"

inline dword FIS_vnExtPartition(void)
{
  TRACEENTER;

  static dword          vnExtPartition = 0;

  if(!vnExtPartition) vnExtPartition = (dword)TryResolve("_nExtPartition");

  TRACEEXIT;
  return vnExtPartition;
}
