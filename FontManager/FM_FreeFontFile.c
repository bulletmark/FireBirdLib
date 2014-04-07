#include                "FBLib_FontManager.h"

void FM_FreeFontFile(tFontData *FontData)
{
  TRACEENTER();

  if(FontData->pFontData)
  {
    TAP_MemFree(FontData->pFontData);
  }
  memset(FontData, 0, sizeof(tFontData));

  TRACEEXIT();
}
