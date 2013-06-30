#include "../libFireBird.h"

inline dword FIS_vHddDivxFolder(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vHddDivxFolder");
  #endif

  static dword          vhddDivxFolder = 0;

  if(!vhddDivxFolder)
    vhddDivxFolder = TryResolve("_hddDivxFolder");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return vhddDivxFolder;
}
