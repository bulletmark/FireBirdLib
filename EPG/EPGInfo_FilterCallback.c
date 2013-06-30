#include                "FBLib_EPG.h"

void EPGInfo_FilterCallback(void *CallbackRoutine)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("EPGInfo_FilterCallback");
  #endif

  if(CallbackRoutine)
  {
    EPGFilter.UseCallback = TRUE;
    EPGFilter.Callback = CallbackRoutine;
  }
  else
  {
    EPGFilter.UseCallback = FALSE;
    EPGFilter.Callback = NULL;
  }

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
