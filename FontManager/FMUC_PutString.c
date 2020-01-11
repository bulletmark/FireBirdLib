#include                <string.h>
#include                "FBLib_FontManager.h"

void FMUC_PutString(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, tFontDataUC *FontData, byte bDot, byte align)
{
  TRACEENTER();

  FMUC_PutStringAA(rgn, x, y, maxX, str, fcolor, bcolor, FontData, bDot, align, 1);

  TRACEEXIT();
}
