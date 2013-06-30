#include "../libFireBird.h"

inline dword FIS_vSelectedPartition(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vSelectedPartition");
  #endif

  static dword          vselectedPartition = 0;

  if(!vselectedPartition) vselectedPartition = (dword)TryResolve("_selectedPartition");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vselectedPartition;
}
