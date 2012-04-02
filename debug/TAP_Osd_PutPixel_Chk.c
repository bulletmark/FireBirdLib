#include                <stdio.h>
#include                "../libFireBird.h"

int TAP_Osd_PutPixel_Chk(char *Comment, word rgn, dword x, dword y, dword pix)
{
  int                   ret;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("TAP_Osd_PutPixel_Chk");
#endif

  if(!isOSDRegionAlive(rgn)) TAP_Print("TAP_Osd_PutPixel_Chk Warning: rgn(%d) points to an undefined region @ %s\n", rgn, Comment);
  if(x > 719) TAP_Print("TAP_Osd_PutPixel_Chk Warning: x(%d) out of range @ %s\n", x, Comment);
  if(y > 575) TAP_Print("TAP_Osd_PutPixel_Chk Warning: y(%d) out of range @ %s\n", y, Comment);

  ret = TAP_Osd_PutPixel(rgn, x, y, pix);

  if(ret) TAP_Print("TAP_Osd_PutPixel_Chk Warning: TAP_Osd_PutPixel() returned %d @ %s\n", ret, Comment);

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return ret;
}
