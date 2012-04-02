#include "FBLib_main.h"

dword FirmwareDatMJD(void)
{
  tFWDATHeader         *FWDatHeader;
  dword                 d;

  if (LoadFirmwareDat(&FWDatHeader, NULL, NULL))
  {

    d = FWDatHeader->CompileDate;
    return TAP_MakeMjd(d >>16, (d >> 8) & 0xff, d & 0xff);
  }

  return 0;
}
