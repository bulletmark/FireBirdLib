#include                "../libFireBird.h"

dword DevHdd_DeviceClose(tDirEntry **hddPlaybackFolder)
{
  dword                 (*__DevHdd_DeviceClose)(tDirEntry **hddPlaybackFolder);
  dword                 ret = 0;

  __DevHdd_DeviceClose = (void*)FIS_fwDevHdd_DeviceClose();
  if(__DevHdd_DeviceClose) ret = __DevHdd_DeviceClose(hddPlaybackFolder);

  return ret;
}
