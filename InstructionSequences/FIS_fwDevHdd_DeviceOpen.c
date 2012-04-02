#include "../libFireBird.h"

inline dword FIS_fwDevHdd_DeviceOpen(void)
{
  static dword          _DevHdd_DeviceOpen = 0;

  if (!_DevHdd_DeviceOpen)
    _DevHdd_DeviceOpen = TryResolve("DevHdd_DeviceOpen");

  return _DevHdd_DeviceOpen;
}
