#include                "../libFireBird.h"

byte DevFront_SetIlluminate(byte a0, byte Brightness)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("DevFront_SetIlluminate");
  #endif

  byte                  (*__DevFront_SetIlluminate)(byte,byte);
  byte                  ret = 0;

  __DevFront_SetIlluminate = (void*)FIS_fwDevFront_SetIlluminate();
  if(__DevFront_SetIlluminate) ret = __DevFront_SetIlluminate(a0, Brightness);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
