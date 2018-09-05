#include "libFireBird.h"

inline dword FIS_vHddDivxFolder(void)
{
  TRACEENTER;

  static dword          vhddDivxFolder = 0;

  if(!vhddDivxFolder)
    vhddDivxFolder = TryResolve("_hddDivxFolder");

  TRACEEXIT;
  return vhddDivxFolder;
}
