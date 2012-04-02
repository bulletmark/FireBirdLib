#include                "FBLib_TMSOSDMenu.h"

void OSDMenuPutS(word rgn, dword x, dword y, dword maxX, const char * str, dword fcolor, dword bcolor, byte fntSize, byte bDot, byte align)
{
  switch(fntSize)
  {
    case 10: FM_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &Calibri_10_FontData, bDot, align, 1); break;
    case 12: FM_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &Calibri_12_FontData, bDot, align, 1); break;
    case 14: FM_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &Calibri_14_FontData, bDot, align, 1); break;
    case 16: FM_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &Calibri_16_FontData, bDot, align, 1); break;
    case 20: FM_PutStringAA(rgn, x, y + FONTYOFFSET, maxX, str, fcolor, bcolor, &Calibri_20_FontData, bDot, align, 1); break;
  }
}
