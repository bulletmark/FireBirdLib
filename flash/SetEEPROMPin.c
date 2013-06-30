#include "FBLib_flash.h"

bool SetEEPROMPin(word NewPin)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("SetEEPROMPin");
  #endif

  word                 *Pin = (word*)FIS_vParentalInfo();

  if(!Pin || (NewPin > 9999))
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  *Pin = NewPin;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
