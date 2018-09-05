#include <string.h>
#include "FBLib_rec.h"

byte *HDD_GetPvrRecTsPlayInfoPointer(byte Slot)
{
  TRACEENTER;

  byte                 *__pvrRecTsPlayInfo;
  byte                 *__pvrRecTempInfo;
  int                   StructSize = 0x774;
  byte                 *ret;

  if(Slot > HDD_NumberOfRECSlots())
  {
    TRACEEXIT;
    return NULL;
  }

  __pvrRecTempInfo = (byte*)FIS_vPvrRecTempInfo();
  if(!__pvrRecTempInfo)
  {
    TRACEEXIT;
    return NULL;
  }

  __pvrRecTsPlayInfo = (byte*)FIS_vPvrRecTsPlayInfo();
  if(!__pvrRecTsPlayInfo)
  {
    TRACEEXIT;
    return NULL;
  }

  StructSize = ((dword)__pvrRecTempInfo - (dword)__pvrRecTsPlayInfo) / (HDD_NumberOfRECSlots() + 1);

  ret = &__pvrRecTsPlayInfo[StructSize * Slot];

  TRACEEXIT;
  return ret;
}
