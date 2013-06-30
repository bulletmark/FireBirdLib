#include "FBLib_main.h"

char *GetToppyString(word SysID)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("GetToppyString");
  #endif

  dword                 i;
  tToppyInfo           *ToppyInfo;
  tFWDATHeader         *FWDatHeader;

  if(LoadFirmwareDat(&FWDatHeader, &ToppyInfo, NULL))
  {
    for(i = 0; i < FWDatHeader->NrOfToppyInfoEntries; i++, ToppyInfo++)
    {
      if(ToppyInfo->SysID == SysID)
      {
        #ifdef DEBUG_FIREBIRDLIB
          CallTraceExit(NULL);
        #endif

        return ToppyInfo->Device;
      }
    }
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return "???";
}
