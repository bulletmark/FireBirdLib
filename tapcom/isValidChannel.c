#include                "FBLib_tapcom.h"

bool isValidChannel (TAPCOM_Channel Channel)
{
  //Gültige Signatur?
  return (((TAPCOM_InternalMesBuf *) Channel)->tapcomSignature == TAPCOM_SIGNATURE);
}
