#include "../flash/FBLib_flash.h"

inline dword FIS_vRECSlotAddress(byte Slot)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("FIS_vRECSlotAddress");
  #endif

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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
