#include                "FBLib_tmsvfd.h"

bool VFD_Clear(void)
{
  TRACEENTER;

  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid)
  {
    TRACEEXIT;
    return FALSE;
  }

  memset(grid, 0, 48);

  TRACEEXIT;
  return TRUE;
}
