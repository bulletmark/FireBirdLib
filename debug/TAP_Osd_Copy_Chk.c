#define                 FB_DEBUG_CHK
#define                 FB_LOG_ENTRY_LIB_PRINTF
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
    if(srcX >= RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: srcX(%lu) >= srcRgnW(%lu) @ %s", srcX, RgnW, Comment);
    if(srcY >= RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: srcY(%lu) >= srcRgnH(%lu) @ %s", srcY, RgnH, Comment);
    if((srcX + w) > RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: (srcX(%lu) + w(%lu)) > srcRgnW(%lu) @ %s", srcX, w, RgnW, Comment);
    if((srcY + h) > RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: (srcY(%lu) + h(%lu)) > srcRgnH(%lu) @ %s", srcY, h, RgnH, Comment);
  }

  RgnH = GetOSDRegionHeight(dstRgnNum);
  RgnW = GetOSDRegionWidth(dstRgnNum);

  if(Comment)
  {
    if(dstX >= RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: dstX(%lu) >= srcRgnW(%lu) @ %s", dstX, RgnW, Comment);
    if(srcY >= RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: srcY(%lu) >= srcRgnH(%lu) @ %s", srcY, RgnH, Comment);
    if((dstX + w) > RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: (dstX(%lu) + w(%lu)) > dstRgnW(%lu) @ %s", dstX, w, RgnW, Comment);
    if((dstY + h) > RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: (dstY(%lu) + h(%lu)) > dstRgnH(%lu) @ %s", dstY, h, RgnH, Comment);
  }

  ret = TAP_Osd_Copy(srcRgnNum, dstRgnNum, srcX, srcY, w, h, dstX, dstY, sprite);

  if(Comment && ret) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Copy_Chk Warning: TAP_Osd_Copy() returned %d @ %s", ret, Comment);

  TRACEEXIT();
  return ret;
}
