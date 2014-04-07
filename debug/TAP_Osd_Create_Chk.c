#include                <stdio.h>
#include                "../libFireBird.h"

int TAP_Osd_Create_Chk(char *Comment, dword x, dword y, dword w, dword h, byte lutIdx, int flag)
{
  TRACEENTER();

  int ret;

  if(Comment)
  {
    if(x > 719) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Create_Chk Warning: x(%d) out of range @ %s", x, Comment);
    if(y > 575) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Create_Chk Warning: y(%d) out of range @ %s", y, Comment);
    if((x + w) > 719) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Create_Chk Warning: x(%d) + w(%d) out of range @ %s", x, w, Comment);
    if((y + h) > 575) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Create_Chk Warning: y(%d) + h(%d) out of range @ %s", y, h, Comment);
  }

  ret = TAP_Osd_Create(x, y, w, h, lutIdx, flag);

  if(Comment && ret < 128) LogEntryFBLibPrintf(TRUE, "TAP_Osd_Create_Chk Warning: TAP_Osd_Create() returned %d @ %s", ret, Comment);

  TRACEEXIT();
  return ret;
}
