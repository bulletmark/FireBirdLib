#include "FBLib_flash.h"

word GetEEPROMPin(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetEEPROMPin");
  #endif

  word                 *Pin = (word*)FIS_vParentalInfo();
  word                  ret;

  ret = (Pin ? *Pin : 0);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
