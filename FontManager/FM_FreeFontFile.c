#include                "FBLib_FontManager.h"

void FM_FreeFontFile(tFontData *FontData)
{
  if(FontData->pFontData)
  {
    TAP_MemFree(FontData->pFontData);
  }
  memset(FontData, 0, sizeof(tFontData));
}
