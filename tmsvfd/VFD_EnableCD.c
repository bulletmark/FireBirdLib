#include                <string.h>
#include                "FBLib_tmsvfd.h"

bool CDEnabled = FALSE;

bool VFD_EnableCD(bool Enable)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("VFD_EnableCD");
  #endif

  byte *grid = (byte*)FIS_vGrid();

  if(!VFDUsedByTAP || !grid)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  if(CDEnabledAnimation) VFD_EnableCDAnimation(FALSE);

  grid[25] &= 0xfc;
  grid[26]  = 0x00;
  grid[27] &= 0x1f;

  if(Enable)
    grid[25] |= 0x02;

  CDEnabled = Enable;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
