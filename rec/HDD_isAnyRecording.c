#include "libFireBird.h"

bool HDD_isAnyRecording(void)
{
  TRACEENTER();

  int                   i, NrRecSlots;
  bool                  ret;

  NrRecSlots = (int)HDD_NumberOfRECSlots();
  ret = FALSE;
  for(i = 0; i < NrRecSlots; i++)
    if(HDD_isRecording(i))
    {
      ret = TRUE;
      break;
    }

  TRACEEXIT();
  return ret;
}
