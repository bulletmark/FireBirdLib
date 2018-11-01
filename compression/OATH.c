#include "libFireBird.h"

dword OATH(register unsigned char *data, int len, dword hash)
{
  TRACEENTER();

  register int i;

  for(i=0; i<len; ++i)
  {
    hash += *data++;
    hash += (hash<<10);
    hash ^= (hash>>6);
  }
  hash += (hash<<3);
  hash ^= (hash>>11);
  hash += (hash<<15);

  TRACEEXIT();
  return hash;
}
