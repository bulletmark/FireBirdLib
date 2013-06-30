#include                "FBLib_tapcom.h"

void TAPCOM_Reject(TAPCOM_Channel Channel)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAPCOM_Reject");
  #endif

  TAPCOM_InternalMesBuf *buf = (TAPCOM_InternalMesBuf *) Channel;

  if(isValidChannel(Channel))
  {
    buf->Status = TAPCOM_Status_REJECTED;

    //Server-Timeout zurücksetzen
    buf->ServerAlive = TAP_GetTick();
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
