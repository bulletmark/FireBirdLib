#include "../libFireBird.h"

inline dword FIS_vSelectedPartition(void)
{
  static dword          vselectedPartition = 0;

  if(!vselectedPartition) vselectedPartition = (dword)TryResolve("_selectedPartition");

  return vselectedPartition;
}
