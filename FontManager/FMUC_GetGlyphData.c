#include <unistd.h>
#include "FBLib_FontManager.h"

tGlyphCacheUC *FMUC_GetGlyphData(tFontDataUC *FontData, byte *UTF8Character, byte *BytesPerChar)
{
  TRACEENTER();

  int                   i;
  dword                 UTF32;
  tGlyphCacheUC        *GC;

  if(!FontData || (FontData->FileHandle <= 0) || !UTF8Character || !*UTF8Character)
  {
    if(BytesPerChar) *BytesPerChar = 1;

    TRACEEXIT();
    return NULL;
  }

  //Code Points 0x00-0x1f and 0x80-0x9f do not contain glyphs
  if((*UTF8Character <= 0x1f) || ((*UTF8Character >= 0x80) && (*UTF8Character <= 0x9f)))
  {
    if(BytesPerChar) *BytesPerChar = 1;

    TRACEEXIT();
    return NULL;
  }

  UTF32 = UTF8ToUTF32(UTF8Character, BytesPerChar);

  //Check if the character is already in the cache
  GC = &FontData->GlyphCache[0];
  for(i = 0; i < (int)FontData->GlyphCacheEntries; i++)
  {
    if(GC->Unicode == UTF32)
    {
      TRACEEXIT();
      return GC;
    }
    GC++;
  }

  //Locate it in the file
  for(i = 0; i < (int)FontData->FontDefEntries; i++)
    if(FontData->FontDef[i].Unicode == UTF32)
    {
      //Create a cache entry for that glyph and return a pointer to it
      tFontDefUC     *FontDef = &FontData->FontDef[i];
      tGlyphCacheUC  *GlyphCache = &FontData->GlyphCache[FontData->GlyphCacheEntries];

      GlyphCache->Unicode = FontDef->Unicode;
      GlyphCache->Width = FontDef->Width;
      GlyphCache->Height = FontDef->Height;

      GlyphCache->GlyphData = FMUC_ReserveMemory("FMUC_GetGlyphData GlyphData", FontDef->Width * FontDef->Height);
      if(GlyphCache->GlyphData == NULL)
      {
        LogEntryFBLibPrintf(TRUE, "FontManager UC: failed to reserve %d bytes for a glyph", FontDef->Width * FontDef->Height);

        TRACEEXIT();
        return NULL;
      }

      lseek(FontData->FileHandle, FontDef->FileOffset, SEEK_SET);
      read(FontData->FileHandle, GlyphCache->GlyphData, FontDef->Width * FontDef->Height);

      FontData->GlyphCacheEntries++;

      TRACEEXIT();
      return GlyphCache;
    }

  //LogEntryFBLibPrintf(TRUE, "Glyph %x not found", UTF32);

  TRACEEXIT();
  return NULL;
}
