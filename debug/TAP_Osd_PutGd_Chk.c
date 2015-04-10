#include                <stdio.h>
#include                "../libFireBird.h"

//TAP_Osd_PutGd(word rgn, int x, int y, TYPE_GrData * gd, bool sprite);

//Checks:
//* Warning if x < 0
//* Warning if y < 0
//* Get width and height of region
//* Warning if srcX >= width
//* Warning if srcY >= height
//* Warning if (srcX + gd.width) >= width
//* Warning if (srcY + gd.height) >= height

int TAP_Osd_PutGd_Chk(char *Comment, word rgn, int x, int y, TYPE_GrData * gd, bool sprite)
{
  TRACEENTER();

  int                   RgnH, RgnW;
  int                   ret;

  if(Comment)
  {
    if(x < 0) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutGd_Chk Warning: x(%d) < 0 @ %s", x, Comment);
    if(y < 0) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutGd_Chk Warning: y(%d) < 0 @ %s", y, Comment);
  }

  if(Comment)
  {
    RgnH = GetOSDRegionHeight(rgn);
    RgnW = GetOSDRegionWidth(rgn);

    if(x >= RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutGd_Chk Warning: x(%d) >= RgnW(%d) @ %s", x, RgnW, Comment);
    if(y >= RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutGd_Chk Warning: y(%d) >= RgnH(%d) @ %s", y, RgnH, Comment);
    if((x + gd->width) > RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutGd_Chk Warning: (x(%d) + gd->width(%d)) > RgnW(%d) @ %s", x, gd->width, RgnW, Comment);
    if((y + gd->height) > RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutGd_Chk Warning: (y(%d) + gd->height(%d)) > RgnH(%d) @ %s", y, gd->height, RgnH, Comment);
  }

  ret = TAP_Osd_PutGd(rgn, x, y, gd, sprite);

  if(Comment && ret) LogEntryFBLibPrintf(TRUE, "TAP_Osd_PutGd_Chk Warning: TAP_Osd_PutGd() returned %d @ %s", ret, Comment);

  TRACEEXIT();
  return ret;
}
