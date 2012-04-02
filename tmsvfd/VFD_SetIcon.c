#include                <string.h>
#include                "FBLib_tmsvfd.h"

bool VFD_SetIcon(tVFDIcon VFDIcon, bool On)
{
  byte *grid = (byte*)FIS_vGrid();
  byte GridIndex = 0, OrBit = 0;

  if(!VFDUsedByTAP || !grid) return FALSE;

  switch(VFDIcon)
  {
    case VFD_AC3        : GridIndex = 27; OrBit = 0; break;
    case VFD_AM         : GridIndex = 39; OrBit = 7; break;
    case VFD_Attn       : GridIndex = 11; OrBit = 4; break;
    case VFD_CDCenter   : GridIndex = 25; OrBit = 1; break;
    case VFD_Clock      : GridIndex = 39; OrBit = 6; break;
    case VFD_Colon      : GridIndex = 37; OrBit = 7; break;
    case VFD_Dolby      : GridIndex = 11; OrBit = 3; break;
    case VFD_Dollar     : GridIndex = 11; OrBit = 5; break;
    case VFD_FFwd       : GridIndex = 10; OrBit = 2; break;
    case VFD_HDD        : GridIndex = 29; OrBit = 4; break;
    case VFD_JumpStart  : GridIndex = 10; OrBit = 5; break;
    case VFD_JumpEnd    : GridIndex = 10; OrBit = 3; break;
    case VFD_MP3        : GridIndex = 28; OrBit = 7; break;
    case VFD_Mute       : GridIndex = 10; OrBit = 0; break;
    case VFD_Network    : GridIndex = 11; OrBit = 2; break;
    case VFD_Pause      : GridIndex = 10; OrBit = 1; break;
    case VFD_Play       : GridIndex = 10; OrBit = 4; break;
    case VFD_PM         : GridIndex = 38; OrBit = 0; break;
    case VFD_Power      : GridIndex = 33; OrBit = 5; break;
    case VFD_Radio      : GridIndex = 27; OrBit = 3; break;
    case VFD_REC        : GridIndex =  9; OrBit = 1; break;
    case VFD_Slot1      : GridIndex =  9; OrBit = 0; break;
    case VFD_Slot2      : GridIndex = 10; OrBit = 7; break;
    case VFD_RepeatLeft : GridIndex = 11; OrBit = 7; break;
    case VFD_RepeatRight: GridIndex = 11; OrBit = 6; break;
    case VFD_Rwd        : GridIndex = 10; OrBit = 6; break;
    case VFD_Satellite  : GridIndex = 27; OrBit = 4; break;
    case VFD_TimeShift  : GridIndex = 27; OrBit = 1; break;
    case VFD_TV         : GridIndex = 27; OrBit = 2; break;
    case VFD_HDDFull    : GridIndex = 28; OrBit = 6; break;
  }

  if(On)
    grid[GridIndex] = grid[GridIndex] | (1 << OrBit);
  else
    grid[GridIndex] = grid[GridIndex] & ~(1 << OrBit);


  return TRUE;
}
