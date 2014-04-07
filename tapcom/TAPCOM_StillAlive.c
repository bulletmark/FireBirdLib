#include                "FBLib_tapcom.h"

void TAPCOM_StillAlive(TAPCOM_Channel Channel)
{
  TRACEENTER();

  if(isValidChannel(Channel))
  {
    //Reset the server timeout
    ((TAPCOM_InternalMesBuf *) Channel)->ServerAlive = TAP_GetTick();
  }

  TRACEEXIT();
}
