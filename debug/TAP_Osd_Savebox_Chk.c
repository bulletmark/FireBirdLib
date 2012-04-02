#include <stdio.h>
#include "../libFireBird.h"

byte* TAP_Osd_SaveBox_Chk(char *Comment, word rgn, dword x, dword y, dword w, dword h)
{
  byte                 *ret;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("TAP_Osd_SaveBox_Chk");
#endif

  if(!isOSDRegionAlive(rgn)) TAP_Print("TAP_Osd_SaveBox_Chk Warning: rgn(%d) points to an undefined region @ %s\n", rgn, Comment);
  if(x > 719) TAP_Print("TAP_Osd_SaveBox_Chk Warning: x(%d) out of range @ %s\n", x, Comment);
  if(y > 575) TAP_Print("TAP_Osd_SaveBox_Chk Warning: y(%d) out of range @ %s\n", y, Comment);
  if((x + w) > 719) TAP_Print("TAP_Osd_SaveBox_Chk Warning: x(%d) + w(%d) out of range @ %s\n", x, w, Comment);
  if((y + h) > 575) TAP_Print("TAP_Osd_SaveBox_Chk Warning: y(%d) + h(%d) out of range @ %s\n", y, h, Comment);

  ret = TAP_Osd_SaveBox(rgn, x, y, w, h);

  if(ret == NULL) TAP_Print("TAP_Osd_SaveBox_Chk Warning: TAP_Osd_SaveBox() returned a NULL pointer @ %s\n", Comment);

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return ret;
}
