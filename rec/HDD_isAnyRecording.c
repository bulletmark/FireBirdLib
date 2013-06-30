#include "../libFireBird.h"

bool HDD_isAnyRecording(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_isAnyRecording");
  #endif

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

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
