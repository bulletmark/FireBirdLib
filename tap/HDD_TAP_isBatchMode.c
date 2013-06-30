#include                <sys/types.h>
#include                <sys/shm.h>
#include                "FBLib_tap.h"

bool HDD_TAP_isBatchMode(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_isBatchMode");
  #endif

  bool ret = (shmget(BATCHMODEKEY, 1, 0) != -1);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
