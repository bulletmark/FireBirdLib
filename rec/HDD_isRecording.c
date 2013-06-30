#include "../libFireBird.h"

bool HDD_isRecording(byte RecSlot)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_isRecording");
  #endif

  TYPE_RecInfo          recInfo;
  bool                  ret;

  ret = (TAP_Hdd_GetRecInfo(RecSlot, &recInfo) && (recInfo.recType == RECTYPE_Normal || recInfo.recType == RECTYPE_Copy));

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
