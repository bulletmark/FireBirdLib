#include  "FBLib_FontManager.h"

bool FMUC_IsDiacriticalMark(dword Character)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FMUC_IsDiacriticalMark");
  #endif

  dword Diacricital[] = {0x00a8, 0x00b4, 0x00b8, 0x0384, 0x0385, 0x0e31};
  dword i;

  if((Character >= 0x0300) && (Character <= 0x036f))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return TRUE;
  }

  if((Character >= 0x0e34) && (Character <= 0x0e3a))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return TRUE;
  }

  if((Character >= 0x0e47) && (Character <= 0x0e4e))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return TRUE;
  }


  for(i = 0; i < 6; i++)
    if(Character == Diacricital[i])
    {
      #ifdef DEBUG_FIREBIRDLIB
        CallTraceExit(NULL);
      #endif

      return TRUE;
    }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FALSE;
}
