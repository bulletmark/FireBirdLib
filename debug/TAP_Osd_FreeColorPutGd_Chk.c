#include                <stdio.h>
#include                "../libFireBird.h"

//int TAP_Osd_PutFreeColorGd(word rgn, int x, int y, TYPE_GrData * gd, bool sprite, dword FilterColor);

//Checks:
//* Warning if x < 0
//* Warning if y < 0
//* Get width and height of region
//* Warning if srcX >= width
//* Warning if srcY >= height
//* Warning if (srcX + gd.width) >= width
//* Warning if (srcY + gd.height) >= height

int TAP_Osd_PutFreeColorGd_Chk(char *Comment, word rgn, int x, int y, TYPE_GrData * gd, bool sprite, dword FilterColor)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAP_Osd_PutFreeColorGd_Chk");
  #endif

  int                   RgnH, RgnW;
  int                   ret;

  if(Comment)
  {
    if(x < 0) TAP_Print("TAP_Osd_PutFreeColorGd_Chk Warning: x(%d) < 0 @ %s\n", x, Comment);
    if(y < 0) TAP_Print("TAP_Osd_PutFreeColorGd_Chk Warning: y(%d) < 0 @ %s\n", y, Comment);
  }

  RgnH = GetOSDRegionHeight(rgn);
  RgnW = GetOSDRegionWidth(rgn);


  if(Comment)
  {
    if(x >= RgnW) TAP_Print("TAP_Osd_PutFreeColorGd_Chk Warning: x(%d) >= RgnW(%d) @ %s\n", x, RgnW, Comment);
    if(y >= RgnH) TAP_Print("TAP_Osd_PutFreeColorGd_Chk Warning: y(%d) >= RgnH(%d) @ %s\n", y, RgnH, Comment);
    if((x + gd->width) > RgnW) TAP_Print("TAP_Osd_PutFreeColorGd_Chk Warning: (x(%d) + gd->width(%d)) > RgnW(%d) @ %s\n", x, gd->width, RgnW, Comment);
    if((y + gd->height) > RgnH) TAP_Print("TAP_Osd_PutFreeColorGd_Chk Warning: (y(%d) + gd->height(%d)) > RgnH(%d) @ %s\n", y, gd->height, RgnH, Comment);
  }

  ret =TAP_Osd_PutFreeColorGd(rgn, x, y, gd, sprite, FilterColor);

  if(Comment && ret) TAP_Print("TAP_Osd_PutFreeColorGd_Chk Warning: TAP_Osd_PutFreeColorGd() returned %d @ %s\n", ret, Comment);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
