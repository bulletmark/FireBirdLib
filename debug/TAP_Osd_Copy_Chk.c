#include                <stdio.h>
#include                "../libFireBird.h"

//TAP_Osd_Copy(word srcRgnNum, word dstRgnNum, dword srcX, dword srcY, dword w, dword h, dword dstX, dword dstY,  bool sprite);

//Checks:
//* Get width and height of source region
//* Warning if srcX >= width
//* Warning if srcY >= height
//* Warning if (srcX + w) >= width
//* Warning if (srcY + h) >= height
//* Get width and height of destination region
//* Warning if dstX >= width
//* Warning if dstY >= height
//* Warning if (dstX + w) >= width
//* Warning if (dstY + h) >= height


int TAP_Osd_Copy_Chk(char *Comment, word srcRgnNum, word dstRgnNum, dword srcX, dword srcY, dword w, dword h, dword dstX, dword dstY,  bool sprite)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAP_Osd_Copy_Chk");
  #endif

  dword                 RgnH, RgnW;
  int                   ret;

  RgnH = GetOSDRegionHeight(srcRgnNum);
  RgnW = GetOSDRegionWidth(srcRgnNum);

  if(Comment)
  {
    if(srcX >= RgnW) TAP_Print("TAP_Osd_Copy_Chk Warning: srcX(%d) >= srcRgnW(%d) @ %s\n", srcX, RgnW, Comment);
    if(srcY >= RgnH) TAP_Print("TAP_Osd_Copy_Chk Warning: srcY(%d) >= srcRgnH(%d) @ %s\n", srcY, RgnH, Comment);
    if((srcX + w) > RgnW) TAP_Print("TAP_Osd_Copy_Chk Warning: (srcX(%d) + w(%d)) > srcRgnW(%d) @ %s\n", srcX, w, RgnW, Comment);
    if((srcY + h) > RgnH) TAP_Print("TAP_Osd_Copy_Chk Warning: (srcY(%d) + h(%d)) > srcRgnH(%d) @ %s\n", srcY, h, RgnH, Comment);
  }

  RgnH = GetOSDRegionHeight(dstRgnNum);
  RgnW = GetOSDRegionWidth(dstRgnNum);

  if(Comment)
  {
    if(dstX >= RgnW) TAP_Print("TAP_Osd_Copy_Chk Warning: dstX(%d) >= srcRgnW(%d) @ %s\n", dstX, RgnW, Comment);
    if(srcY >= RgnH) TAP_Print("TAP_Osd_Copy_Chk Warning: srcY(%d) >= srcRgnH(%d) @ %s\n", srcY, RgnH, Comment);
    if((dstX + w) > RgnW) TAP_Print("TAP_Osd_Copy_Chk Warning: (dstX(%d) + w(%d)) > dstRgnW(%d) @ %s\n", dstX, w, RgnW, Comment);
    if((dstY + h) > RgnH) TAP_Print("TAP_Osd_Copy_Chk Warning: (dstY(%d) + h(%d)) > dstRgnH(%d) @ %s\n", dstY, h, RgnH, Comment);
  }

  ret = TAP_Osd_Copy(srcRgnNum, dstRgnNum, srcX, srcY, w, h, dstX, dstY, sprite);

  if(Comment && ret) TAP_Print("TAP_Osd_Copy_Chk Warning: TAP_Osd_Copy() returned %d @ %s\n", ret, Comment);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
