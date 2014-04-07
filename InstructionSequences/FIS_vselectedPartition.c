#include "../libFireBird.h"

inline dword FIS_vSelectedPartition(void)
{
  TRACEENTER();

  static dword          vselectedPartition = 0;

  if(!vselectedPartition) vselectedPartition = (dword)TryResolve("_selectedPartition");

  TRACEEXIT();
  return vselectedPartition;
}
