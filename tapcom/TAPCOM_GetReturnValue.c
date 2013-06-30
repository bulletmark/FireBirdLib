#include                "FBLib_tapcom.h"

int TAPCOM_GetReturnValue(TAPCOM_Channel Channel)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("TAPCOM_GetReturnValue");
  #endif

  int ret;
  TAPCOM_InternalMesBuf *buf = (TAPCOM_InternalMesBuf *) Channel;

  if(!isValidChannel(Channel) || (buf->Status != TAPCOM_Status_FINISHED))
    ret = TAPCOM_NO_RETURN_VALUE;
  else
    ret = buf->ReturnVal;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
