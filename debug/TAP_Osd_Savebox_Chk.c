#undef FB_NO_DEBUG
#include "libFireBird.h"

byte* TAP_Osd_SaveBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h)
{
  TRACEENTER();

  byte                 *ret;
  dword                 RgnH, RgnW;

  if(Comment)
  {
    RgnH = GetOSDRegionHeight(rgn);
    RgnW = GetOSDRegionWidth(rgn);

    if(!isOSDRegionAlive(rgn)) LogEntryFBLibPrintf(TRUE, "TAP_Osd_SaveBox_Chk Warning: rgn(%d) points to an undefined region @ %s", rgn, Comment);
    if(x >= RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_SaveBox_Chk Warning: x(%d) out of range @ %s", x, Comment);
    if(y >= RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_SaveBox_Chk Warning: y(%d) out of range @ %s", y, Comment);
    if((x + w) > RgnW) LogEntryFBLibPrintf(TRUE, "TAP_Osd_SaveBox_Chk Warning: x(%d) + w(%d) out of range @ %s", x, w, Comment);
    if((y + h) > RgnH) LogEntryFBLibPrintf(TRUE, "TAP_Osd_SaveBox_Chk Warning: y(%d) + h(%d) out of range @ %s", y, h, Comment);
  }

  ret = TAP_Osd_SaveBox(rgn, x, y, w, h);

  if(Comment) if(ret == NULL) LogEntryFBLibPrintf(TRUE, "TAP_Osd_SaveBox_Chk Warning: TAP_Osd_SaveBox() returned a NULL pointer @ %s", Comment);

  TRACEEXIT();
  return ret;
}
