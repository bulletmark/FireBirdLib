#include "FBLib_main.h"

dword FirmwareDatMJD(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FirmwareDatMJD");
  #endif

  tFWDATHeader         *FWDatHeader;
  dword                 d;

  if(LoadFirmwareDat(&FWDatHeader, NULL, NULL))
  {
    d = FWDatHeader->CompileDate;

    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return TAP_MakeMjd(d >>16, (d >> 8) & 0xff, d & 0xff);
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return 0;
}
