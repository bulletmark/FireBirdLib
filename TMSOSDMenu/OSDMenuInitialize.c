#include                "FBLib_TMSOSDMenu.h"

void OSDMenuInitialize(bool AllowScrollingOfLongText, bool HasValueColumn, bool NumberedItems, bool ScrollLoop, const char *TitleLeft, const char *TitleRight)
{
  TRACEENTER();

  if(OSDRgn) TAP_Osd_Delete(OSDRgn);
  OSDRgn = 0;
  MyOSDRgn = 0;

  OSDMenuInit(AllowScrollingOfLongText, HasValueColumn, NumberedItems, ScrollLoop, TitleLeft, TitleRight);

  OSDMenuButtonsClear();

  TRACEEXIT();
}
