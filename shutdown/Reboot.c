#include "FBLib_shutdown.h"
#include "../libFireBird.h"

bool Reboot(bool StopRecordings)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Reboot");
  #endif

  if(StopRecordings || !HDD_isAnyRecording()) TAP_Reboot();

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return TRUE;
}
