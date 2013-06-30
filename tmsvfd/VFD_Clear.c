#include                "FBLib_tmsvfd.h"

bool VFD_Clear(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("VFD_Clear");
  #endif

  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  memset(grid, 0, 48);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
