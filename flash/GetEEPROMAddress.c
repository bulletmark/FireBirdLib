#include "FBLib_flash.h"

dword GetEEPROMAddress(void)
{
  dword ret;

  TRACEENTER;

  ret = FIS_vEEPROM();

  TRACEEXIT;
  return ret;
}
