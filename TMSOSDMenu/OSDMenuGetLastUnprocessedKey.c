#include                "FBLib_TMSOSDMenu.h"

dword OSDMenuGetLastUnprocessedKey(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("OSDMenuGetLastUnprocessedKey");
  #endif

  dword                 ret;

  ret = LastUnprocessedOSDMenuKey;
  LastUnprocessedOSDMenuKey = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
  return ret;
}
