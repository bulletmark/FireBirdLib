#include                <string.h>
#include                "FBLib_tmsvfd.h"

bool VFD_SetHDDValue(int Percent)
{
  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid || !HDDEnabled) return FALSE;

  VFD_EnableHDD(TRUE);

  if(Percent > 11) grid[29] |= 0x20;
  if(Percent > 22) grid[29] |= 0x40;
  if(Percent > 33) grid[29] |= 0x80;
  if(Percent > 44) grid[28] |= 0x01;
  if(Percent > 55) grid[28] |= 0x02;
  if(Percent > 66) grid[28] |= 0x04;
  if(Percent > 77) grid[28] |= 0x08;
  if(Percent > 88) grid[28] |= 0x10;

  return TRUE;
}
