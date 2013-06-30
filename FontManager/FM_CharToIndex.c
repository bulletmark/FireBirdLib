#include                "FBLib_FontManager.h"

byte FM_CharToIndex(byte Char)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FM_CharToIndex");
  #endif

  //0x20 - 0x7e
  //0xa0 - 0xff
  if(!FM_isValidCharacter(Char)) Char = 0x20;

  if(Char > 0x7e) Char -= 0x21;
  Char -= 0x20;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return (byte)Char;
}
