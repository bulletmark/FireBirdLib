#include                "../libFireBird.h"

byte *SkipCharTableBytes(byte *p)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("SkipCharTableBytes");
  #endif

  byte                 *ret;

  if((p == NULL) || (*p == '\0'))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return p;
  }

  ret = p;
  if(*ret < ' ')
  {
    if(*ret == 0x10)
      ret += 2;
    else if(*ret == 0x1f)
      ret++;

    ret++;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
