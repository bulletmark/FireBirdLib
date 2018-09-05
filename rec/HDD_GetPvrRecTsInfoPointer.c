#include <string.h>
#include "FBLib_rec.h"

byte *HDD_GetPvrRecTsInfoPointer(byte Slot)
{
  TRACEENTER;

  static byte          *__pvrRecTsInfo = NULL;
  static byte          *__pvrRecTsPlayInfo = NULL;
  static int            infSize = 1412;
  byte                 *ret;

  if(Slot > HDD_NumberOfRECSlots())
  {
    TRACEEXIT;
    return NULL;
  }

  if(!HDD_GetRecSlotFiles(Slot, NULL, NULL, NULL))
  {
    TRACEEXIT;
    return NULL;
  }

  if(!__pvrRecTsInfo)
  {
    __pvrRecTsInfo = (byte*)FIS_vPvrRecTsInfo();
    if(!__pvrRecTsInfo)
    {
      TRACEEXIT;
      return NULL;
    }
  }

  if(!__pvrRecTsPlayInfo)
  {
    __pvrRecTsPlayInfo = (byte*)FIS_vPvrRecTsPlayInfo();
    if(!__pvrRecTsPlayInfo)
    {
      TRACEEXIT;
      return NULL;
    }

    infSize = ((dword)__pvrRecTsPlayInfo - (dword)__pvrRecTsInfo) / (HDD_NumberOfRECSlots() + 1);
  }

  ret = &__pvrRecTsInfo[infSize * Slot];

  TRACEEXIT;
  return ret;
}
