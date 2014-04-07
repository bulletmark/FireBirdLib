#include                "FBLib_FontManager.h"

byte FM_CharToIndex(byte Char)
{
  TRACEENTER();

  //0x20 - 0x7e
  //0xa0 - 0xff
  if(!FM_isValidCharacter(Char)) Char = 0x20;

  if(Char > 0x7e) Char -= 0x21;
  Char -= 0x20;

  TRACEEXIT();
  return (byte)Char;
}
