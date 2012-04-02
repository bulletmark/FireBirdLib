#include "../libFireBird.h"

inline dword FIS_vHddDivxFolder(void)
{
  static dword          vhddDivxFolder = 0;

  if (!vhddDivxFolder)
    vhddDivxFolder = TryResolve("_hddDivxFolder");

  return vhddDivxFolder;
}
