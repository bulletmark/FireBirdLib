#include "../libFireBird.h"

inline dword FIS_vTAPTable(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vTAPTable");
  #endif

  static dword          *vTAP_TableAddress = NULL;

  if(!vTAP_TableAddress) vTAP_TableAddress = (dword*)TryResolve("_tapTask");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (dword)vTAP_TableAddress;
}
