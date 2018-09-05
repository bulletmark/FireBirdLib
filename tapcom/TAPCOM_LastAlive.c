#include                "FBLib_tapcom.h"

dword TAPCOM_LastAlive(TAPCOM_Channel Channel)
{
  TRACEENTER;

  dword ret;

  if(isValidChannel(Channel))
    ret = ((TAPCOM_InternalMesBuf *) Channel)->ServerAlive;
  else
    ret = 0;

  TRACEEXIT;
  return ret;
}
