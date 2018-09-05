#include                <string.h>
#include                "FBLib_FontManager.h"

dword FMUC_GetStringWidth(char *Text, tFontDataUC *FontData)
{
  TRACEENTER;

  dword                 Width = 0;
  tGlyphCacheUC        *GlyphData;
  byte                 *p, *pEnd;
  byte                  BytesPerChar;

  if(!Text || !Text[0] || !FontData)
  {
    TRACEEXIT;
    return 0;
  }

  p = Text;
  pEnd = p + strlen(Text);

  while(p < pEnd)
  {
    GlyphData = FMUC_GetGlyphData(FontData, p, &BytesPerChar);
    if(GlyphData && !FMUC_IsDiacriticalMark(UTF8ToUTF32(p, NULL))) Width += GlyphData->Width;
    p += BytesPerChar;
  }

  TRACEEXIT;
  return Width;
}
