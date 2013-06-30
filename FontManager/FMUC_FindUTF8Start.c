#include  "FBLib_FontManager.h"

byte *FMUC_FindUTF8Start(byte *p)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FMUC_FindUTF8Start");
  #endif

  if(p == NULL)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  //Find the first byte of a multibyte UTF-8 character
  while((*p & 0xc0) == 0x80) p--;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return p;
}
