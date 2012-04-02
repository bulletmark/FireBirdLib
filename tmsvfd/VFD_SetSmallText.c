#include                <string.h>
#include                "FBLib_tmsvfd.h"

bool VFD_SetSmallText(char *Text)
{
  dword                 i;
  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid) return FALSE;

  if (Text)
  {
    i = strlen (Text);

    if (i > 0) VFD_SetDisplayDigit (grid, Text[0], VFD_14, 0);
          else VFD_SetDisplayDigit (grid, ' ', VFD_14, 0);
    if (i > 1) VFD_SetDisplayDigit (grid, Text[1], VFD_14, 1);
          else VFD_SetDisplayDigit (grid, ' ', VFD_14, 1);
    if (i > 2) VFD_SetDisplayDigit (grid, Text[2], VFD_14, 2);
          else VFD_SetDisplayDigit (grid, ' ', VFD_14, 2);
    if (i > 3) VFD_SetDisplayDigit (grid, Text[3], VFD_14, 3);
          else VFD_SetDisplayDigit (grid, ' ', VFD_14, 3);
  }
  return TRUE;
}
