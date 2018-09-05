#include "FBLib_flash.h"

word GetEEPROMPin(void)
{
  TRACEENTER;

  word                 *Pin = (word*)FIS_vParentalInfo();
  word                  ret;

  ret = (Pin ? *Pin : 0);

  TRACEEXIT;
  return ret;
}
