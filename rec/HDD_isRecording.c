#include "../libFireBird.h"

bool HDD_isRecording(byte RecSlot)
{
  TYPE_RecInfo          recInfo;

  return (TAP_Hdd_GetRecInfo(RecSlot, &recInfo) && (recInfo.recType == RECTYPE_Normal || recInfo.recType == RECTYPE_Copy));
}
