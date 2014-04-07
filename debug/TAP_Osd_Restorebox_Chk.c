#include <stdio.h>
#include "../libFireBird.h"

void TAP_Osd_RestoreBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h, void *data)
{
  TRACEENTER();

  if(Comment)
  {
    if(!isOSDRegionAlive(rgn)) LogEntryFBLibPrintf(TRUE, "TAP_Osd_RestoreBox_Chk Warning: rgn(%d) points to an undefined region @ %s", rgn, Comment);
    if(x > 719) LogEntryFBLibPrintf(TRUE, "TAP_Osd_RestoreBox_Chk Warning: x(%d) out of range @ %s", x, Comment);
    if(y > 575) LogEntryFBLibPrintf(TRUE, "TAP_Osd_RestoreBox_Chk Warning: y(%d) out of range @ %s", y, Comment);
    if((x + w) > 719) LogEntryFBLibPrintf(TRUE, "TAP_Osd_RestoreBox_Chk Warning: x(%d) + w(%d) out of range @ %s", x, w, Comment);
    if((y + h) > 575) LogEntryFBLibPrintf(TRUE, "TAP_Osd_RestoreBox_Chk Warning: y(%d) + h(%d) out of range @ %s", y, h, Comment);
    if(data == NULL) LogEntryFBLibPrintf(TRUE, "TAP_Osd_RestoreBox_Chk Warning: trying to restore from NULL @ %s", Comment);
  }

  TAP_Osd_RestoreBox(rgn, x, y, w, h, data);

  TRACEEXIT();
}
