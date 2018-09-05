#include                <string.h>
#include                "FBLib_tmsvfd.h"

bool VFD_SetLargeText(char *Text)
{
  TRACEENTER;

  dword                 i;

  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid)
  {
    TRACEEXIT;
    return FALSE;
  }

  if(Text)
  {
    i = strlen(Text);

    if(i > 0) VFD_SetDisplayDigit(grid, Text[0], VFD_17, 0);
         else VFD_SetDisplayDigit(grid, ' ', VFD_17, 0);
    if(i > 1) VFD_SetDisplayDigit(grid, Text[1], VFD_17, 1);
         else VFD_SetDisplayDigit(grid, ' ', VFD_17, 1);
    if(i > 2) VFD_SetDisplayDigit(grid, Text[2], VFD_17, 2);
         else VFD_SetDisplayDigit(grid, ' ', VFD_17, 2);
    if(i > 3) VFD_SetDisplayDigit(grid, Text[3], VFD_17, 3);
         else VFD_SetDisplayDigit(grid, ' ', VFD_17, 3);
    if(i > 4) VFD_SetDisplayDigit(grid, Text[4], VFD_17, 4);
         else VFD_SetDisplayDigit(grid, ' ', VFD_17, 4);
    if(i > 5) VFD_SetDisplayDigit(grid, Text[5], VFD_17, 5);
         else VFD_SetDisplayDigit(grid, ' ', VFD_17, 5);
    if(i > 6) VFD_SetDisplayDigit(grid, Text[6], VFD_17, 6);
         else VFD_SetDisplayDigit(grid, ' ', VFD_17, 6);
    if(i > 7) VFD_SetDisplayDigit(grid, Text[7], VFD_17, 7);
         else VFD_SetDisplayDigit(grid, ' ', VFD_17, 7);
  }

  TRACEEXIT;
  return TRUE;
}
