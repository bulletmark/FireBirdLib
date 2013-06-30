#include "FBLib_rec.h"

bool HDD_RecSlotEncode(byte Slot, tFlashTimer *RecSlot)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_RecSlotEncode");
  #endif

  dword                 RSA;
  bool                  ret;

  //Sanity check of the parameters
  if(Slot > HDD_NumberOfRECSlots())
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  RSA = FIS_vRECSlotAddress(Slot);
  if(RSA == 0)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return FALSE;
  }

  ret = FlashTimerEncode((void*)RSA, RecSlot);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
