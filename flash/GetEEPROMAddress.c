#include "FBLib_flash.h"

dword GetEEPROMAddress(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetEEPROMAddress");
  #endif

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return FIS_vEEPROM();
}
