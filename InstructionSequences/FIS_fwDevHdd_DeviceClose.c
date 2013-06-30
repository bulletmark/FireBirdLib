#include "../libFireBird.h"

inline dword FIS_fwDevHdd_DeviceClose(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_fwDevHdd_DeviceClose");
  #endif

  static dword          _DevHdd_DeviceClose = 0;

  if(!_DevHdd_DeviceClose)
    _DevHdd_DeviceClose = TryResolve("DevHdd_DeviceClose");

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _DevHdd_DeviceClose;
}
