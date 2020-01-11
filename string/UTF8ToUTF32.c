#include "libFireBird.h"

dword UTF8ToUTF32(const byte *UTF8Character, byte *BytesPerChar)
{
  TRACEENTER();

  byte c1, c2, c3, c4;

  if(BytesPerChar) *BytesPerChar = 1;
  if(!UTF8Character)
  {
    TRACEEXIT();
    return 0;
  }

  //0xxx xxxx
  c1 = UTF8Character[0];
  if((c1 & 0x80) == 0x00)
  {
    TRACEEXIT();
    return c1;
  }

  //110x xxxx 10xx xxxx
  c2 = UTF8Character[1];
  if(((c1 & 0xe0) == 0xc0) &&
     ((c2 & 0xc0) == 0x80))
  {
    if(BytesPerChar) *BytesPerChar = 2;

    TRACEEXIT();
    return ((c1 & 0x1f) << 6) | (c2 & 0x3f);
  }

  //1110 xxxx 10xx xxxx 10xx xxxx
  c3 = UTF8Character[2];
  if(((c1 & 0xf0) == 0xe0) &&
     ((c2 & 0xc0) == 0x80) &&
     ((c3 & 0xc0) == 0x80))
  {
    if(BytesPerChar) *BytesPerChar = 3;

    TRACEEXIT();
    return ((c1 & 0x0f) << 12) | ((c2 & 0x3f) << 6) | (c3 & 0x3f);
  }

  //1111 0xxx 10xx xxxx 10xx xxxx 10xx xxxx
  c4 = UTF8Character[3];
  if(((c1 & 0xf8) == 0xf0) &&
     ((c2 & 0xc0) == 0x80) &&
     ((c3 & 0xc0) == 0x80) &&
     ((c4 & 0xc0) == 0x80))
  {
    if(BytesPerChar) *BytesPerChar = 4;

    TRACEEXIT();
    return ((c1 & 0x07) << 18) | ((c2 & 0x3f) << 12) | ((c3 & 0x3f) << 6) | (c4 & 0x3f);
  }

  //Malformed packet, return that character
  TRACEEXIT();
  return c1;
}
