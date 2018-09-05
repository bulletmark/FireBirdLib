#include "libFireBird.h"

bool HDD_isRecording(byte RecSlot)
{
  TRACEENTER;

  TYPE_RecInfo          recInfo;
  bool                  ret;

  ret = (TAP_Hdd_GetRecInfo(RecSlot, &recInfo) && (recInfo.recType == RECTYPE_Normal || recInfo.recType == RECTYPE_Copy));

  TRACEEXIT;
  return ret;
}
