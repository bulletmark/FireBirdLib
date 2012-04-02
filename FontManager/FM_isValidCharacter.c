#include                "FBLib_FontManager.h"

bool FM_isValidCharacter(byte Char)
{
  if(Char < 0x20) return FALSE;
  if((Char > 0x7e) && (Char < 0xa0)) return FALSE;

  return TRUE;
}
