#include                "../libFireBird.h"

dword DevHdd_DeviceOpen(tDirEntry **hddPlaybackFolder, tDirEntry *DirEntry)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("DevHdd_DeviceOpen");
  #endif

  dword                 (*__DevHdd_DeviceOpen)(tDirEntry **hddPlaybackFolder, tDirEntry *DirEntry);
  dword                 ret = 0;

  __DevHdd_DeviceOpen = (void*)FIS_fwDevHdd_DeviceOpen();
  if(__DevHdd_DeviceOpen) ret = __DevHdd_DeviceOpen(hddPlaybackFolder, DirEntry);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
