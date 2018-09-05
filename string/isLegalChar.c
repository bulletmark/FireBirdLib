#include "FBLib_string.h"

bool isLegalChar(byte *c, eRemoveChars ControlCharacters)
{
  TRACEENTER;

  byte s;

  if(c == NULL)
  {
    TRACEEXIT;
    return FALSE;
  }

  s = *c;

  if((ControlCharacters & ControlChars) != 0)
  {
    // Anything below 32 is a control character!
    if((s < 0x20) && (s != 0x0a))
    {
      TRACEEXIT;
      return FALSE;
    }

    //Before destroying some bytes, check if this is a UTF8 character
    if(!isUTF8Char(c, NULL))
    {
      // these characters are unused in Windows system font and cause trouble
      if((s >= 0x7f) && (s <= 0x9f) && (s != 0x80) && (s != 0x8a) && (s != 0x91) && (s != 0x92))
      {
        TRACEEXIT;
        return FALSE;
      }
    }
  }

  if((ControlCharacters & LFChars) != 0)
  {
    if((s == 0x0a) || (s == 0x8a))
    {
      TRACEEXIT;
      return FALSE;
    }
  }

  if((ControlCharacters & InvalidFileNameChars) != 0)
  {
    switch(s)
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
      {
        TRACEEXIT;
        return FALSE;
      }
    }
  }

  if((ControlCharacters & NonPrintableChars) != 0)
  {
    TRACEEXIT;
    return (s >= ' ' && s <= '~');
  }

  TRACEEXIT;
  return TRUE;
}
