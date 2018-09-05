#include "FBLib_flash.h"

bool SetEEPROMPin(word NewPin)
{
  TRACEENTER;

  word                 *Pin = (word*)FIS_vParentalInfo();

  if(!Pin || (NewPin > 9999))
  {
    TRACEEXIT;
    return FALSE;
  }

  *Pin = NewPin;

  TRACEEXIT;
  return TRUE;
}
