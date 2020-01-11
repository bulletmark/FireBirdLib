#include                "FBLib_TMSOSDMenu.h"

void OSDMenuPutS(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, byte fntSize, byte bDot, byte align)
{
  TRACEENTER();

  switch(fntSize)
  {
    case 10: FMUC_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &OSDMenuFont_10, bDot, align, 1); break;
    case 12: FMUC_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &OSDMenuFont_12, bDot, align, 1); break;
    case 14: FMUC_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &OSDMenuFont_14, bDot, align, 1); break;
    case 16: FMUC_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &OSDMenuFont_16, bDot, align, 1); break;
    case 18: FMUC_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &OSDMenuFont_18, bDot, align, 1); break;
    case 20: FMUC_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &OSDMenuFont_20, bDot, align, 1); break;
    case 20+0xB: FMUC_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &OSDMenuFont_20B, bDot, align, 1); break;
  }

  TRACEEXIT();
}
