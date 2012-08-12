#include                "../libFireBird.h"

byte CharToISO(byte *p)
{
  byte ret;

  if(!p) return 0;

  if(!isUTF8Char(p)) return *p;

  //In our case, we just support 2-byte UTF8 codes because the Toppy doesn't use Unicode strings
  ret = ((p[0] & 0x03) << 6) | (p[1] & 0x3f);

  return ret;
}
