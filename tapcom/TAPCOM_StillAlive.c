#include                "FBLib_tapcom.h"

void TAPCOM_StillAlive(TAPCOM_Channel Channel)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAPCOM_StillAlive");
  #endif

  if(isValidChannel(Channel))
  {
    //Reset the server timeout
    ((TAPCOM_InternalMesBuf *) Channel)->ServerAlive = TAP_GetTick();
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
