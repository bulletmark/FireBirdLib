#include "FBLib_string.h"

bool isLegalChar(byte *c, eRemoveChars ControlCharacters)
{
  byte s;

  if(c == NULL) return FALSE;

  s = *c;

  if ((ControlCharacters & ControlChars) != 0)
  {
    // Anything below 32 is a control character!
    if((s < 0x20) && (s != 0x0a)) return FALSE;

    //Before destroying some bytes, check if this is a UTF8 character
    if(!isUTF8Char(c))
    {
      // these characters are unused in Windows system font and cause trouble
      if((s >= 0x7f) && (s <= 0x9f) && (s != 0x80) && (s != 0x8a) && (s != 0x91) && (s != 0x92)) return FALSE;

      //Control codes used by some channels
      if((s == 0x05) || (s == 0x86) || (s == 0x87)) return FALSE;
    }
  }

  if ((ControlCharacters & LFChars) != 0)
  {
    if ((s == 0x0a) || (s == 0x8a)) return FALSE;
  }

  if ((ControlCharacters & InvalidFileNameChars) != 0)
  {
    switch (s)
    {
      // this character will cause a filename not displayed in recording list
      // Remarked for UTF8 compatibility
      // case 'à':

      // These characters are not allowed in Windows.
      case ':':
      case '/':
      case '\\':
      case '*':
      case '?':
      case '"':
      case '<':
      case '>':
      case '|':
        return FALSE;
        break;
    }
  }

  if ((ControlCharacters & NonPrintableChars) != 0) return (s >= ' ' && s <= '~');

  return TRUE;
}
