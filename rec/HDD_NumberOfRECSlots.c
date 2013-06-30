#include "FBLib_rec.h"

dword HDD_NumberOfRECSlots(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_NumberOfRECSlots");
  #endif

  static dword          MaxRecStreams = 0;
  dword                 i;
  tToppyInfo           *ToppyInfo;
  tFWDATHeader         *FWDatHeader;

  if(MaxRecStreams == 0)
  {
    if(LoadFirmwareDat(&FWDatHeader, &ToppyInfo, NULL))
    {
      for(i = 0; i < FWDatHeader->NrOfToppyInfoEntries; i++, ToppyInfo++)
      {
        if(ToppyInfo->SysID == GetSysID())
        {
          MaxRecStreams = ToppyInfo->MaxRecStreams;
          break;
        }
      }
    }

    if(MaxRecStreams == 0) MaxRecStreams = 2;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return MaxRecStreams;
}
