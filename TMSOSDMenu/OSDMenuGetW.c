#include                "FBLib_TMSOSDMenu.h"

#include                "fonts/Calibri_10.c"
#include                "fonts/Calibri_12.c"
#include                "fonts/Calibri_14.c"
#include                "fonts/Calibri_16.c"
#include                "fonts/Calibri_18.c"
#include                "fonts/Calibri_20.c"
#include                "fonts/Calibri_20B.c"

int OSDMenuGetW(const char * str, byte fntSize)
{
  switch(fntSize)
  {
    case 10: return FM_GetStringWidth(str, &Calibri_10_FontData);
    case 12: return FM_GetStringWidth(str, &Calibri_12_FontData);
    case 14: return FM_GetStringWidth(str, &Calibri_14_FontData);
    case 16: return FM_GetStringWidth(str, &Calibri_16_FontData);
    case 20: return FM_GetStringWidth(str, &Calibri_20_FontData);
  }

  return 0;
}
