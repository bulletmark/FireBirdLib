#include "../libFireBird.h"
#include "FBLib_rec.h"

bool HDD_RecSlotDecode(byte Slot, tFlashTimer *RecSlot)
{
  dword                 RSA;

  //Sanity check of the parameters
  if (Slot > HDD_NumberOfRECSlots()) return FALSE;

  RSA = FIS_vRECSlotAddress(Slot);
  if(RSA == 0) return FALSE;

  return FlashTimerDecode((void*)RSA, RecSlot);
}
