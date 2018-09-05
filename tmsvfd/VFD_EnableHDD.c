#include                <string.h>
#include                "FBLib_tmsvfd.h"

bool HDDEnabled = FALSE;

bool VFD_EnableHDD(bool Enable)
{
  TRACEENTER;

  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid)
  {
    TRACEEXIT;
    return FALSE;
  }

  grid[29] &= 0x1f;
  grid[28] &= 0xC0;

  if(Enable)
    grid[28] |= 0x20;

  HDDEnabled = Enable;

  TRACEEXIT;
  return TRUE;
}
