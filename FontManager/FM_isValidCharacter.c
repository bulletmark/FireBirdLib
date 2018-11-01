#include                "FBLib_FontManager.h"

bool FM_isValidCharacter(byte Char)
{
  TRACEENTER();

  bool ret = TRUE;

  if(Char < 0x20) ret = FALSE;
  if((Char > 0x7e) && (Char < 0xa0)) ret = FALSE;

  TRACEEXIT();
  return ret;
}
