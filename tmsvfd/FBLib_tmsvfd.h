#ifndef FBLIB_TMSVFD_H
#define FBLIB_TMSVFD_H

#include "libFireBird.h"

typedef enum
{
  VFD_7,
  VFD_14,
  VFD_17
} DISPLAYSTYLE;

extern bool  VFDUsedByTAP;
extern byte *grid;
extern bool  CDEnabled;
extern bool  CDEnabledAnimation;
extern bool  HDDEnabled;
extern tVFDCharset CurrentCharset;

dword VFD_TranslateSegments(byte Character, DISPLAYSTYLE DisplayStyle);
void  VFD_SetDisplayDigit (byte* DisplayBuffer, byte Character, DISPLAYSTYLE DisplayStyle, byte Digit);

#endif
