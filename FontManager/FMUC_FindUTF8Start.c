#include  "FBLib_FontManager.h"

byte *FMUC_FindUTF8Start(byte *p)
{
  TRACEENTER;

  if(p == NULL)
  {
    TRACEEXIT;
    return NULL;
  }

  //Find the first byte of a multibyte UTF-8 character
  while((*p & 0xc0) == 0x80) p--;

  TRACEEXIT;
  return p;
}
