#include                "libFireBird.h"

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
  TRACEENTER();

  dword                 RgnH, RgnW;
  int                   ret;

  RgnH = GetOSDRegionHeight(srcRgnNum);
  RgnW = GetOSDRegionWidth(srcRgnNum);

  if(Comment)
  {
    if(srcX >= RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: srcX(%d) >= srcRgnW(%d) @ %s", srcX, RgnW, Comment);
    if(srcY >= RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: srcY(%d) >= srcRgnH(%d) @ %s", srcY, RgnH, Comment);
    if((srcX + w) > RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: (srcX(%d) + w(%d)) > srcRgnW(%d) @ %s", srcX, w, RgnW, Comment);
    if((srcY + h) > RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: (srcY(%d) + h(%d)) > srcRgnH(%d) @ %s", srcY, h, RgnH, Comment);
  }

  RgnH = GetOSDRegionHeight(dstRgnNum);
  RgnW = GetOSDRegionWidth(dstRgnNum);

  if(Comment)
  {
    if(dstX >= RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: dstX(%d) >= srcRgnW(%d) @ %s", dstX, RgnW, Comment);
    if(srcY >= RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: srcY(%d) >= srcRgnH(%d) @ %s", srcY, RgnH, Comment);
    if((dstX + w) > RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: (dstX(%d) + w(%d)) > dstRgnW(%d) @ %s", dstX, w, RgnW, Comment);
    if((dstY + h) > RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: (dstY(%d) + h(%d)) > dstRgnH(%d) @ %s", dstY, h, RgnH, Comment);
  }

  ret = TAP_Osd_Copy(srcRgnNum, dstRgnNum, srcX, srcY, w, h, dstX, dstY, sprite);

  if(Comment && ret) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: TAP_Osd_Copy() returned %d @ %s", ret, Comment);

  TRACEEXIT();
  return ret;
}
