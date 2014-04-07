#include                <string.h>
#include                "FBLib_tmsvfd.h"

//Animation: AGBH
//           CIBH
//           CIDJ
//           EKDJ
//           EKFL
//           AGFL

bool VFD_CDAnimation(bool Forward)
{
  TRACEENTER();

  static int            Counter = 0;
  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid || !CDEnabledAnimation)
  {
    TRACEEXIT();
    return FALSE;
  }

  grid[25] &= 0xfe;
  grid[26]  = 0x00;
  grid[27] &= 0x1f;

  if(Forward)
    Counter++;
  else
    Counter--;

  if(Counter > 5) Counter = 0;
  if(Counter < 0) Counter = 5;

  switch(Counter)
  {
    case 0:
    {
      grid[25] |= 0x01; //A
      grid[26] |= 0x04; //G
      grid[26] |= 0x80; //B
      grid[26] |= 0x02; //H
      break;
    }

    case 1:
    {
      grid[26] |= 0x40; //C
      grid[26] |= 0x01; //I
      grid[26] |= 0x80; //B
      grid[26] |= 0x02; //H
      break;
    }

    case 2:
    {
      grid[26] |= 0x40; //C
      grid[26] |= 0x01; //I
      grid[26] |= 0x20; //D
      grid[27] |= 0x80; //J
      break;
    }

    case 3:
    {
      grid[26] |= 0x10; //E
      grid[27] |= 0x40; //K
      grid[26] |= 0x20; //D
      grid[27] |= 0x80; //J
      break;
    }

    case 4:
    {
      grid[26] |= 0x10; //E
      grid[27] |= 0x40; //K
      grid[26] |= 0x08; //F
      grid[27] |= 0x20; //L
      break;
    }

    case 5:
    {
      grid[25] |= 0x01; //A
      grid[26] |= 0x04; //G
      grid[26] |= 0x08; //F
      grid[27] |= 0x20; //L
      break;
    }
  }

  TRACEEXIT();
  return TRUE;
}
