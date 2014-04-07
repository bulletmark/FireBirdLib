#include                "../libFireBird.h"

byte *SkipCharTableBytes(byte *p)
{
  TRACEENTER();

  byte                 *ret;

  if((p == NULL) || (*p == '\0'))
  {
    TRACEEXIT();
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

  TRACEEXIT();
  return ret;
}
