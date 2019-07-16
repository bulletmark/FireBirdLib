#include "FBLib_TMSOSDMenu.h"

int OSDMenuGetH (char *str, byte fntSize)
{
  int ret = 0;

  TRACEENTER();

  switch (fntSize)
  {
    case 10: ret = FMUC_GetStringHeight(str, &OSDMenuFont_10); break;
    case 12: ret = FMUC_GetStringHeight(str, &OSDMenuFont_12); break;
    case 14: ret = FMUC_GetStringHeight(str, &OSDMenuFont_14); break;
    case 16: ret = FMUC_GetStringHeight(str, &OSDMenuFont_16); break;
    case 18: ret = FMUC_GetStringHeight(str, &OSDMenuFont_18); break;
    case 20: ret = FMUC_GetStringHeight(str, &OSDMenuFont_20); break;
    case 20+0xB: ret = FMUC_GetStringHeight(str, &OSDMenuFont_20B); break;
  }

  TRACEEXIT();

  return ret;
}
