#include "libFireBird.h"

inline dword FIS_fwDevHdd_DeviceClose(void)
{
  TRACEENTER;

  static dword          _DevHdd_DeviceClose = 0;

  if(!_DevHdd_DeviceClose)
    _DevHdd_DeviceClose = TryResolve("DevHdd_DeviceClose");

  TRACEEXIT;
  return _DevHdd_DeviceClose;
}
