#include                <sys/types.h>
#include                <sys/shm.h>
#include                "FBLib_tap.h"

bool HDD_TAP_isBatchMode(void)
{
  TRACEENTER;

  bool ret = (shmget(BATCHMODEKEY, 1, 0) != -1);

  TRACEEXIT;
  return ret;
}
