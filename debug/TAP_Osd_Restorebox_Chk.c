#include <stdio.h>
#include "../libFireBird.h"

void TAP_Osd_RestoreBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h, void *data)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAP_Osd_RestoreBox_Chk");
  #endif

  if(Comment)
  {
    if(!isOSDRegionAlive(rgn)) TAP_Print("TAP_Osd_RestoreBox_Chk Warning: rgn(%d) points to an undefined region @ %s\n", rgn, Comment);
    if(x > 719) TAP_Print("TAP_Osd_RestoreBox_Chk Warning: x(%d) out of range @ %s\n", x, Comment);
    if(y > 575) TAP_Print("TAP_Osd_RestoreBox_Chk Warning: y(%d) out of range @ %s\n", y, Comment);
    if((x + w) > 719) TAP_Print("TAP_Osd_RestoreBox_Chk Warning: x(%d) + w(%d) out of range @ %s\n", x, w, Comment);
    if((y + h) > 575) TAP_Print("TAP_Osd_RestoreBox_Chk Warning: y(%d) + h(%d) out of range @ %s\n", y, h, Comment);
    if(data == NULL) TAP_Print("TAP_Osd_RestoreBox_Chk Warning: trying to restore from NULL @ %s\n", Comment);
  }

  TAP_Osd_RestoreBox(rgn, x, y, w, h, data);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
