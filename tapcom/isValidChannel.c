#include                "FBLib_tapcom.h"

bool isValidChannel(TAPCOM_Channel Channel)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("isValidChannel");
  #endif

  //Gültige Signatur?
  bool ret = (((TAPCOM_InternalMesBuf *) Channel)->tapcomSignature == TAPCOM_SIGNATURE);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
