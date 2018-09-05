#include                "FBLib_tapcom.h"

int TAPCOM_GetReturnValue(TAPCOM_Channel Channel)
{
  TRACEENTER;

  int ret;
  TAPCOM_InternalMesBuf *buf = (TAPCOM_InternalMesBuf *) Channel;

  if(!isValidChannel(Channel) || (buf->Status != TAPCOM_Status_FINISHED))
    ret = TAPCOM_NO_RETURN_VALUE;
  else
    ret = buf->ReturnVal;

  TRACEEXIT;
  return ret;
}
