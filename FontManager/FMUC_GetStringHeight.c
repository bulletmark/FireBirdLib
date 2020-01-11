#include                <string.h>
#include                "FBLib_FontManager.h"

dword FMUC_GetStringHeight(const char *Text, tFontDataUC *FontData)
{
  TRACEENTER();

  tGlyphCacheUC        *GlyphData;
  const byte           *p, *pEnd;
  byte                  BytesPerChar;
  dword                 Height = 0;

  if(!Text || !Text[0] || !FontData)
  {
    TRACEEXIT();
    return 0;
  }

  p = Text;
  pEnd = p + strlen(Text);

  while(p < pEnd)
  {
    GlyphData = FMUC_GetGlyphData(FontData, p, &BytesPerChar);
    if(GlyphData && (GlyphData->Height > Height)) Height = GlyphData->Height;
    p += BytesPerChar;
  }

  TRACEEXIT();
  return Height;
}
