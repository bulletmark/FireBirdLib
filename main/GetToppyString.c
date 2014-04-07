#include "FBLib_main.h"

char *GetToppyString(word SysID)
{
  TRACEENTER();

  dword                 i;
  tToppyInfo           *ToppyInfo;
  tFWDATHeader         *FWDatHeader;

  if(LoadFirmwareDat(&FWDatHeader, &ToppyInfo, NULL))
  {
    for(i = 0; i < FWDatHeader->NrOfToppyInfoEntries; i++, ToppyInfo++)
    {
      if(ToppyInfo->SysID == SysID)
      {
        TRACEEXIT();
        return ToppyInfo->Device;
      }
    }
  }

  TRACEEXIT();
  return "???";
}
