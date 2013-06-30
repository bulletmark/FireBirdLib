#include                <stdio.h>
#include                "../libFireBird.h"

int TAP_Osd_FillBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h, dword color)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAP_Osd_FillBox_Chk");
  #endif

  int                   ret;

  if(Comment)
  {
    if(!isOSDRegionAlive(rgn)) TAP_Print("TAP_Osd_FillBox_Chk Warning: rgn(%d) points to an undefined region @ %s\n", rgn, Comment);
    if(x > 719) TAP_Print("TAP_Osd_FillBox_Chk Warning: x(%d) out of range @ %s\n", x, Comment);
    if(y > 575) TAP_Print("TAP_Osd_FillBox_Chk Warning: y(%d) out of range @ %s\n", y, Comment);
    if((x + w) > 719) TAP_Print("TAP_Osd_FillBox_Chk Warning: x(%d) + w(%d) out of range @ %s\n", x, w, Comment);
    if((y + h) > 575) TAP_Print("TAP_Osd_FillBox_Chk Warning: y(%d) + h(%d) out of range @ %s\n", y, h, Comment);
  }

  ret = TAP_Osd_FillBox(rgn, x, y, w, h, color);

  if(Comment && ret) TAP_Print("TAP_Osd_FillBox_Chk Warning: TAP_Osd_Create() returned %d @ %s\n", ret, Comment);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
