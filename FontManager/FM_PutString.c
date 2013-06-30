#include                <string.h>
#include                "FBLib_FontManager.h"

void FM_PutString(word rgn, dword x, dword y, dword maxX, char * str, dword fcolor, dword bcolor, tFontData *FontData, byte bDot, byte align)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FM_PutString");
  #endif

  FM_PutStringAA(rgn, x, y, maxX, str, fcolor, bcolor, FontData, bDot, align, 1);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
