#include "FBLib_rec.h"

bool HDD_RecSlotEncode(byte Slot, tFlashTimer *RecSlot)
{
  dword                 RSA;

  //Sanity check of the parameters
  if (Slot > HDD_NumberOfRECSlots()) return FALSE;

  RSA = FIS_vRECSlotAddress(Slot);
  if(RSA == 0) return FALSE;

  return FlashTimerEncode((void*)RSA, RecSlot);
}
