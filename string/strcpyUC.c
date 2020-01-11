#include                <string.h>
#include                "libFireBird.h"

byte *strcpyUC(byte *dest, const byte *src)
{
  TRACEENTER();

  byte                 *p;
  int                   CharTableBytes;

  if(!src || !dest)
  {
    TRACEEXIT();
    return NULL;
  }

  p = SkipCharTableBytes(src);
  CharTableBytes = p - src;

  if(CharTableBytes == 0)
    strcpy(dest, src);
  else
  {
    memcpy(dest, (void *) src, CharTableBytes);
    strcpy(&dest[CharTableBytes], p);
  }

  TRACEEXIT();
  return dest;
}
