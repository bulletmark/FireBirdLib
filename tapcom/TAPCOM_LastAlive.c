#include                "FBLib_tapcom.h"

dword TAPCOM_LastAlive(TAPCOM_Channel Channel)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAPCOM_LastAlive");
  #endif

  dword ret;

  if(isValidChannel(Channel))
    ret = ((TAPCOM_InternalMesBuf *) Channel)->ServerAlive;
  else
    ret = 0;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
