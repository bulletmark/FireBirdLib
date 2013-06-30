#include                "FBLib_TMSOSDMenu.h"

bool OSDMenuPush(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuPush");
  #endif

  if(CurrentMenuLevel >= (NRMENULEVELS - 1))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  CurrentMenuLevel++;
  memset(&Menu[CurrentMenuLevel], 0, sizeof(tMenu));

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
