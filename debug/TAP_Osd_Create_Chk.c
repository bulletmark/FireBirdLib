#include                <stdio.h>
#include                "../libFireBird.h"

int TAP_Osd_Create_Chk(char *Comment, dword x, dword y, dword w, dword h, byte lutIdx, int flag)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAP_Osd_Create_Chk");
  #endif

  int ret;

  if(Comment)
  {
    if(x > 719) TAP_Print("TAP_Osd_Create_Chk Warning: x(%d) out of range @ %s\n", x, Comment);
    if(y > 575) TAP_Print("TAP_Osd_Create_Chk Warning: y(%d) out of range @ %s\n", y, Comment);
    if((x + w) > 719) TAP_Print("TAP_Osd_Create_Chk Warning: x(%d) + w(%d) out of range @ %s\n", x, w, Comment);
    if((y + h) > 575) TAP_Print("TAP_Osd_Create_Chk Warning: y(%d) + h(%d) out of range @ %s\n", y, h, Comment);
  }

  ret = TAP_Osd_Create(x, y, w, h, lutIdx, flag);

  if(Comment && ret < 128) TAP_Print("TAP_Osd_Create_Chk Warning: TAP_Osd_Create() returned %d @ %s\n", ret, Comment);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
