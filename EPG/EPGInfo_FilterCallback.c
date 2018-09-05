#include                "FBLib_EPG.h"

void EPGInfo_FilterCallback(void *CallbackRoutine)
{
  TRACEENTER;

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

  TRACEEXIT;
}
