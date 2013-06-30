#include                <string.h>
#include                "FBLib_tmsvfd.h"

bool HDDEnabled = FALSE;

bool VFD_EnableHDD(bool Enable)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("VFD_EnableHDD");
  #endif

  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  grid[29] &= 0x1f;
  grid[28] &= 0xC0;

  if(Enable)
    grid[28] |= 0x20;

  HDDEnabled = Enable;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
