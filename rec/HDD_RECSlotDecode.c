#include "../libFireBird.h"
#include "FBLib_rec.h"

bool HDD_RecSlotDecode(byte Slot, tFlashTimer *RecSlot)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_RecSlotDecode");
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

  ret = FlashTimerDecode((void*)RSA, RecSlot);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
