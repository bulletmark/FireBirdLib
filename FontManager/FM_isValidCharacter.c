#include                "FBLib_FontManager.h"

bool FM_isValidCharacter(byte Char)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FM_isValidCharacter");
  #endif

  bool ret = TRUE;

  if(Char < 0x20) ret = FALSE;
  if((Char > 0x7e) && (Char < 0xa0)) ret = FALSE;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
