#include                <sys/types.h>
#include                <sys/shm.h>
#include                "FBLib_tap.h"


bool HDD_TAP_StartedByTAP(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_StartedByTAP");
  #endif

  bool ret = (shmget(PARAMBLOCKKEY, sizeof(TYPE_Parametered_Tap), 0) != -1);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
