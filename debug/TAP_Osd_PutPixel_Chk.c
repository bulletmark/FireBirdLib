#include                <stdio.h>
#include                "../libFireBird.h"

int TAP_Osd_PutPixel_Chk(char *Comment, word rgn, dword x, dword y, dword pix)
{
  TRACEENTER();

  int                   ret;
  dword                 RgnH, RgnW;

  if(Comment)
  {
    RgnH = GetOSDRegionHeight(rgn);
    RgnW = GetOSDRegionWidth(rgn);

    if(!isOSDRegionAlive(rgn)) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutPixel_Chk Warning: rgn(%d) points to an undefined region @ %s", rgn, Comment);
    if(x >= RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutPixel_Chk Warning: x(%d) out of range @ %s", x, Comment);
    if(y >= RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutPixel_Chk Warning: y(%d) out of range @ %s", y, Comment);
  }

  ret = TAP_Osd_PutPixel(rgn, x, y, pix);

  if(Comment && ret) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutPixel_Chk Warning: TAP_Osd_PutPixel() returned %d @ %s", ret, Comment);

  TRACEEXIT();
  return ret;
}
