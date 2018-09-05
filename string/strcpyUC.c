#include                <string.h>
#include                "libFireBird.h"

byte *strcpyUC(byte *dest, byte *src)
{
  TRACEENTER;

  byte                 *p;
  int                   CharTableBytes;

  if(!src || !dest)
  {
    TRACEEXIT;
    return NULL;
  }

  p = SkipCharTableBytes(src);
  CharTableBytes = p - src;

  if(CharTableBytes == 0)
    strcpy(dest, src);
  else
  {
    memcpy(dest, src, CharTableBytes);
    strcpy(&dest[CharTableBytes], p);
  }

  TRACEEXIT;
  return dest;
}
