#include                "FBLib_tmsvfd.h"

bool VFD_Clear(void)
{
  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid) return FALSE;

  memset(grid, 0, 48);

  return TRUE;
}
