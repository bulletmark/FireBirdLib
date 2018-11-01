#include "FBLib_av.h"
#include "libFireBird.h"

void EndMessageWin(void)
{
  TRACEENTER();

  if(fbl_rgn) TAP_Osd_Delete(fbl_rgn);
  fbl_rgn = 0;
  TAP_Osd_Sync();

  TRACEEXIT();
}
