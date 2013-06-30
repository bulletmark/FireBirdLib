#include "../libFireBird.h"

bool isPIPActive(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isPIPActive");
  #endif

  byte *_isPipActive = (byte*)FIS_vIsPipActive();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return _isPipActive ? *_isPipActive : FALSE;
}
