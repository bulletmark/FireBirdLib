#include                "FBLib_FontManager.h"

void FM_FreeFontFile(tFontData *FontData)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FM_FreeFontFile");
  #endif

  if(FontData->pFontData)
  {
    TAP_MemFree(FontData->pFontData);
  }
  memset(FontData, 0, sizeof(tFontData));

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
