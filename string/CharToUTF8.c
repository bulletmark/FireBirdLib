#include                "../libFireBird.h"

dword CharToUTF8(byte *p)
{
  if(!p) return 0;

  if(*p < 0x80) return *p;

  return 0xc080 | ((*p & 0xc0) << 2) | (*p & 0x3f);
}
