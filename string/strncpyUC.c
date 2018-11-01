#include                <string.h>
#include                "libFireBird.h"

byte *strncpyUC(byte *dest, byte *src, size_t n)
{
  TRACEENTER();

  byte                 *p;
  size_t                CharTableBytes;

  if(!src || !dest)
  {
    TRACEEXIT();
    return NULL;
  }

  p = SkipCharTableBytes(src);
  CharTableBytes = p - src;

  if(CharTableBytes == 0)
    strncpy(dest, src, n);
  else
  {
    memcpy(dest, src, CharTableBytes < n ? CharTableBytes : n);
    strncpy(&dest[CharTableBytes], p, n - CharTableBytes);
  }

  TRACEEXIT();
  return dest;
}
