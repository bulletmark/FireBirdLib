#include                "FBLib_tapcom.h"

void TAPCOM_CloseChannel(TAPCOM_Channel Channel)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAPCOM_CloseChannel");
  #endif

  TAPCOM_InternalMesBuf *buf = (TAPCOM_InternalMesBuf *) Channel;

  if(isValidChannel(Channel) && (buf->FromID == __tap_ud__))
  {
    buf->tapcomSignature = 0;
    TAP_MemFree(Channel);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
