#include "../libFireBird.h"

inline dword FIS_fwDevHdd_DeviceOpen(void)
{
  TRACEENTER();

  static dword          _DevHdd_DeviceOpen = 0;

  if(!_DevHdd_DeviceOpen)
    _DevHdd_DeviceOpen = TryResolve("DevHdd_DeviceOpen");

  TRACEEXIT();
  return _DevHdd_DeviceOpen;
}
