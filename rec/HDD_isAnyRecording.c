#include "../libFireBird.h"

bool HDD_isAnyRecording(void)
{
  int                   i, NrRecSlots;

  NrRecSlots = (int)HDD_NumberOfRECSlots();
  for(i = 0; i < NrRecSlots; i++)
    if(HDD_isRecording(i)) return TRUE;

  return FALSE;
}
