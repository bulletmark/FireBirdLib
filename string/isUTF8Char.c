#include                "../libFireBird.h"

bool isUTF8Char(byte *p)
{
  bool                  a, b, c;

  if(!p || !isUTFToppy()) return FALSE;

  a = ((p[0] & 0xe0) == 0xc0) && ((p[1] & 0xc0) == 0x80);
  b = ((p[0] & 0xf0) == 0xe0) && ((p[1] & 0xc0) == 0x80) && ((p[2] & 0xc0) == 0x80);
  c = ((p[0] & 0xf8) == 0xf0) && ((p[1] & 0xc0) == 0x80) && ((p[2] & 0xc0) == 0x80)  && ((p[3] & 0xc0) == 0x80);

  return (a || b || c);
}
