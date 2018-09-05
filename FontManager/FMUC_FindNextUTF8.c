#include  "FBLib_FontManager.h"

byte *FMUC_FindNextUTF8(byte *p)
{
  TRACEENTER;

  if(p == NULL)
  {
    TRACEEXIT;
    return NULL;
  }

  //Find the next start byte of a multibyte UTF-8 character
  p++;
  while((*p & 0xc0) == 0x80) p++;

  TRACEEXIT;
  return p;
}
