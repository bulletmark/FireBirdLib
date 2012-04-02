#include "FBLib_shutdown.h"
#include "../libFireBird.h"

bool Reboot(bool StopRecordings)
{
  if(StopRecordings || !HDD_isAnyRecording()) TAP_Reboot();

  return TRUE;
}
