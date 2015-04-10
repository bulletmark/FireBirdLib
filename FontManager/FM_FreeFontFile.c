#include                <stdlib.h>
#include                "FBLib_FontManager.h"

#undef malloc
#undef free

void FM_FreeFontFile(tFontData *FontData)
{
  TRACEENTER();

  free(FontData->pFontData);
  memset(FontData, 0, sizeof(tFontData));

  TRACEEXIT();
}
