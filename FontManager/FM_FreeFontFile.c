#include                <stdlib.h>
#include                "FBLib_FontManager.h"

void FM_FreeFontFile(tFontData *FontData)
{
  TRACEENTER;

  TAP_MemFree(FontData->pFontData);
  memset(FontData, 0, sizeof(tFontData));

  TRACEEXIT;
}
