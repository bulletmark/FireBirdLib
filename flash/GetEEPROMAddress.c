#include "FBLib_flash.h"

dword GetEEPROMAddress (void)
{
  return FIS_vEEPROM();
}
