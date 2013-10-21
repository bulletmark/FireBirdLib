#include <string.h>
#include "FBLib_rec.h"

byte *HDD_GetPvrRecTsPlayInfoPointer(byte Slot)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_GetPvrRecTsPlayInfoPointer");
  #endif

  byte                 *__pvrRecTsPlayInfo;
  byte                 *__pvrRecTempInfo;
  int                   StructSize = 0x774;
  byte                 *ret;

  if(Slot > HDD_NumberOfRECSlots())
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  __pvrRecTempInfo = (byte*)FIS_vPvrRecTempInfo();
  if(!__pvrRecTempInfo)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  __pvrRecTsPlayInfo = (byte*)FIS_vPvrRecTsPlayInfo();
  if(!__pvrRecTsPlayInfo)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  StructSize = ((dword)__pvrRecTempInfo - (dword)__pvrRecTsPlayInfo) / (HDD_NumberOfRECSlots() + 1);

  ret = &__pvrRecTsPlayInfo[StructSize * Slot];

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
