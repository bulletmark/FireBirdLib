#include                <unistd.h>
#include                "FBLib_FontManager.h"

void FMUC_FreeFontFile(tFontDataUC *FontData)
{
  TRACEENTER;

  dword     i;

  if(FontData)
  {
    for(i = 0; i < FontData->GlyphCacheEntries; i++)
      if(FontData->GlyphCache[i].GlyphData) FMUC_FreeMemory("FMUC_FreeFontFile", FontData->GlyphCache[i].GlyphData);

    if(FontData->GlyphCache) FMUC_FreeMemory("FMUC_FreeFontFile", FontData->GlyphCache);
    if(FontData->FontDef) FMUC_FreeMemory("FMUC_FreeFontFile", FontData->FontDef);
    if(FontData->FileHandle) close(FontData->FileHandle);

    memset(FontData, 0, sizeof(tFontDataUC));
  }

  TRACEEXIT;
}
