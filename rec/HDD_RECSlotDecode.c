#include "libFireBird.h"
#include "FBLib_rec.h"

bool HDD_RecSlotDecode(byte Slot, tFlashTimer *RecSlot)
{
  TRACEENTER();

  dword                 RSA;
  bool                  ret;

  //Sanity check of the parameters
  if(Slot > HDD_NumberOfRECSlots())
  {
    TRACEEXIT();
    return FALSE;
  }

  RSA = FIS_vRECSlotAddress(Slot);
  if(RSA == 0)
  {
    TRACEEXIT();
    return FALSE;
  }

  ret = FlashTimerDecode((void*)RSA, RecSlot);

  TRACEEXIT();
  return ret;
}
