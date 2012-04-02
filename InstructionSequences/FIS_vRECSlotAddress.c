#include "../flash/FBLib_flash.h"

inline dword FIS_vRECSlotAddress(byte Slot)
{
  static byte          *__pvrRecInfo = NULL;

  if (Slot > HDD_NumberOfRECSlots()) return 0;

  if(!__pvrRecInfo)
  {
    __pvrRecInfo = (byte*)TryResolve("_pvrRecInfo");
    if(!__pvrRecInfo) return 0;
  }

  return (dword)&__pvrRecInfo[Slot * FlashTimerStructSize()];
}
