#include                "FBLib_tapcom.h"

bool isValidChannel(TAPCOM_Channel Channel)
{
  TRACEENTER();

  //Gültige Signatur?
  bool ret = (((TAPCOM_InternalMesBuf *) Channel)->tapcomSignature == TAPCOM_SIGNATURE);

  TRACEEXIT();
  return ret;
}
