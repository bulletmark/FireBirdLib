#include                "../libFireBird.h"

dword DevHdd_DeviceClose(tDirEntry **hddPlaybackFolder)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("DevHdd_DeviceClose");
  #endif

  dword                 (*__DevHdd_DeviceClose)(tDirEntry **hddPlaybackFolder);
  dword                 ret = 0;

  __DevHdd_DeviceClose = (void*)FIS_fwDevHdd_DeviceClose();
  if(__DevHdd_DeviceClose) ret = __DevHdd_DeviceClose(hddPlaybackFolder);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
