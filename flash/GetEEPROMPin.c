#include "FBLib_flash.h"

word GetEEPROMPin(void)
{
  word                 *Pin = (word*)FIS_vParentalInfo();

  return (Pin ? *Pin : 0);
}
