#include "../libFireBird.h"

inline dword FIS_fwDevHdd_DeviceOpen(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwDevHdd_DeviceOpen");
  #endif

  static dword          _DevHdd_DeviceOpen = 0;

  if(!_DevHdd_DeviceOpen)
    _DevHdd_DeviceOpen = TryResolve("DevHdd_DeviceOpen");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _DevHdd_DeviceOpen;
}
