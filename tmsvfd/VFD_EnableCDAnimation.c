#include                <string.h>
#include                "FBLib_tmsvfd.h"

bool CDEnabledAnimation = FALSE;

bool VFD_EnableCDAnimation(bool Enable)
{
  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid) return FALSE;

  if(CDEnabled) VFD_EnableCD(FALSE);

  grid[25] &= 0xfc;
  grid[26]  = 0x00;
  grid[27] &= 0x1f;

  if(Enable)
    grid[25] |= 0x02;

  CDEnabledAnimation = Enable;

  return TRUE;
}
