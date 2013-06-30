#include  "FBLib_FontManager.h"

byte *FMUC_FindNextUTF8(byte *p)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FMUC_FindNextUTF8");
  #endif

  if(p == NULL)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  //Find the next start byte of a multibyte UTF-8 character
  p++;
  while((*p & 0xc0) == 0x80) p++;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return p;
}
