#include                "libFireBird.h"

SYSTEM_TYPE GetSystemType(void)
{
  TRACEENTER();

  static SYSTEM_TYPE    SystemType = ST_UNKNOWN;
  tToppyInfo           *ToppyInfo;
  tFWDATHeader         *FWDatHeader;
  int                   i;

  if(SystemType == ST_UNKNOWN)
  {
    if(LoadFirmwareDat(&FWDatHeader, &ToppyInfo, NULL))
    {
      for(i = 0; i < (int)FWDatHeader->NrOfToppyInfoEntries; i++, ToppyInfo++)
      {
        if(ToppyInfo->SysID == GetSysID())
        {
          SystemType = ToppyInfo->SystemType;

          TRACEEXIT();
          return SystemType;
        }
      }
    }
  }

  TRACEEXIT();
  return SystemType;
}
