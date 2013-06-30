#include                <string.h>
#include                "FBLib_FontManager.h"

dword FMUC_GetStringHeight(char *Text, tFontDataUC *FontData)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FMUC_GetStringHeight");
  #endif

  tGlyphCacheUC        *GlyphData;
  byte                 *p, *pEnd;
  byte                  BytesPerChar;
  dword                 Height = 0;

  if(!Text || !Text[0] || !FontData)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return 0;
  }

  p = Text;
  pEnd = p + strlen(Text);

  while(p < pEnd)
  {
    GlyphData = FMUC_GetGlyphData(FontData, p, &BytesPerChar);
    if(GlyphData)
    {
      if(GlyphData->Height > Height) Height = GlyphData->Height;
    }
    p += BytesPerChar;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return Height;
}
