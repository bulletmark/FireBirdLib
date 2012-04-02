#include <string.h>
#include "FBLib_rec.h"

byte *HDD_GetPvrRecTsInfoPointer(byte Slot)
{
  TYPE_RecInfo          RecInfo;
  static byte          *__pvrRecTsInfo = NULL;
  static byte          *__pvrRecTsPlayInfo = NULL;
  static int            infSize = 1412;

  if(Slot >= HDD_NumberOfRECSlots()) return NULL;

  TAP_Hdd_GetRecInfo(Slot, &RecInfo);
  if(RecInfo.recType != RECTYPE_Normal) return NULL;

  if(!__pvrRecTsInfo)
  {
    __pvrRecTsInfo = (byte*)FIS_vPvrRecTsInfo();
    if(!__pvrRecTsInfo) return NULL;
  }

  if(!__pvrRecTsPlayInfo)
  {
    __pvrRecTsPlayInfo = (byte*)FIS_vPvrRecTsPlayInfo();
    if(!__pvrRecTsPlayInfo) return NULL;

    infSize = ((dword)__pvrRecTsPlayInfo - (dword)__pvrRecTsInfo) / (HDD_NumberOfRECSlots() + 1);
  }

  return &__pvrRecTsInfo[infSize * Slot];
}
