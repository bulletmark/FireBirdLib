#include "../libFireBird.h"

inline dword FIS_vIsAllPartitionInvalid(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vIsAllPartitionInvalid");
  #endif

  static dword          visAllPartitionInvalid = 0;

  if(!visAllPartitionInvalid)
    visAllPartitionInvalid = (dword)TryResolve("_isAllPartitionInvalid");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return visAllPartitionInvalid;
}
