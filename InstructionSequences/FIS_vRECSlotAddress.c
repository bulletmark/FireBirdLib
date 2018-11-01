#include "flash/FBLib_flash.h"

inline dword FIS_vRECSlotAddress(byte Slot)
{
  TRACEENTER();

  static byte          *__pvrRecInfo = NULL;
  dword                 ret;

  if(Slot > HDD_NumberOfRECSlots())
    ret = 0;
  else
  {
    if(!__pvrRecInfo)
    {
      __pvrRecInfo = (byte*)TryResolve("_pvrRecInfo");
      if(!__pvrRecInfo) return 0;
    }

    ret = (dword)&__pvrRecInfo[Slot * FlashTimerStructSize()];
  }

  TRACEEXIT();
  return ret;
}
