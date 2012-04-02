#include                <sys/types.h>
#include                <sys/shm.h>
#include                "FBLib_tap.h"


bool HDD_TAP_StartedByTAP (void)
{
  return (shmget(PARAMBLOCKKEY, sizeof(TYPE_Parametered_Tap), 0) != -1);
}
