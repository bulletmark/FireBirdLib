#include "../libFireBird.h"

void UTF32ToUTF8(dword UTF32Character, byte *UTF8Character, byte *BytesPerChar)
{
  TRACEENTER();

  //Just 1 byte needed
  if(UTF32Character < 0x80)
  {
    if(UTF8Character) *UTF8Character = UTF32Character;

    if(BytesPerChar) *BytesPerChar = 1;

    TRACEEXIT();
    return;
  }

  //2 bytes needed
  if(UTF32Character < 0x800)
  {

    if(UTF8Character)
    {
      UTF8Character[0] = 0xc0 | ((UTF32Character >> 6) & 0x1f);
      UTF8Character[1] = 0x80 | (UTF32Character & 0x3f);
    }

    if(BytesPerChar) *BytesPerChar = 2;

    TRACEEXIT();
    return;
  }

  //3 bytes needed
  if(UTF32Character < 0x1000)
  {

    if(UTF8Character)
    {
      UTF8Character[0] = 0xc0 | ((UTF32Character >> 12) & 0x0f);
      UTF8Character[1] = 0x80 | ((UTF32Character >> 6) & 0x3f);
      UTF8Character[2] = 0x80 | (UTF32Character & 0x3f);
    }

    if(BytesPerChar) *BytesPerChar = 3;

    TRACEEXIT();
    return;
  }

  //4 bytes needed
  if(UTF8Character)
  {
    UTF8Character[0] = 0xc0 | ((UTF32Character >> 18) & 0x07);
    UTF8Character[1] = 0x80 | ((UTF32Character >> 12) & 0x3f);
    UTF8Character[1] = 0x80 | ((UTF32Character >> 6) & 0x3f);
    UTF8Character[2] = 0x80 | (UTF32Character & 0x3f);
  }

  if(BytesPerChar) *BytesPerChar = 4;

  TRACEEXIT();
}
