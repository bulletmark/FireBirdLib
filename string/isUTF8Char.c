#include                "../libFireBird.h"

bool isUTF8Char(byte *p)
{
  if(!p) return FALSE;

  if((p[0] < 0xc0) || (p[0] > 0xdf) || (p[1] < 0x80) || (p[1] > 0xbf)) return FALSE;

  return TRUE;
}
