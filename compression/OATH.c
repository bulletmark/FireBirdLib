#include "../libFireBird.h"

dword OATH(register unsigned char *data, int len, dword hash)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OATH");
  #endif

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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return hash;
}
