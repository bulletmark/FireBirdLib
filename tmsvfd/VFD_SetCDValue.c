#include                <string.h>
#include                "FBLib_tmsvfd.h"

bool VFD_SetCDValue(int Percent)
{
  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid || !CDEnabled) return FALSE;

  grid[25] &= 0xfe;
  grid[26]  = 0x00;
  grid[27] &= 0x1f;

  if(Percent >  7) grid[25] |= 0x01;
  if(Percent > 15) grid[26] |= 0x80;
  if(Percent > 23) grid[26] |= 0x40;
  if(Percent > 30) grid[26] |= 0x20;
  if(Percent > 38) grid[26] |= 0x10;
  if(Percent > 46) grid[26] |= 0x08;
  if(Percent > 53) grid[26] |= 0x04;
  if(Percent > 61) grid[26] |= 0x02;
  if(Percent > 69) grid[26] |= 0x01;
  if(Percent > 76) grid[27] |= 0x80;
  if(Percent > 84) grid[27] |= 0x40;
  if(Percent > 92) grid[27] |= 0x20;

  return TRUE;
}
