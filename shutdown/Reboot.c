#include "FBLib_shutdown.h"
#include "libFireBird.h"

bool Reboot(bool StopRecordings)
{
  TRACEENTER();

  if(StopRecordings || !HDD_isAnyRecording()) TAP_Reboot();

  TRACEEXIT();
  return TRUE;
}
