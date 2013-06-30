#include                <sys/types.h>
#include                <sys/shm.h>
#include                "FBLib_tap.h"

void *HDD_TAP_GetStartParameter(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("HDD_TAP_GetStartParameter");
  #endif

  int                   shmidParameterBlock;
  void                 *ret;

  shmidParameterBlock = shmget(PARAMBLOCKKEY, sizeof(TYPE_Parametered_Tap), 0);
  if(shmidParameterBlock == -1)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  fbl_parametered_tap = (TYPE_Parametered_Tap*)shmat(shmidParameterBlock, 0, 0);
  if((int)fbl_parametered_tap == -1)
  {
    #ifdef DEBUG_FIREBIRDLIB
      CallTraceExit(NULL);
    #endif

    return NULL;
  }

  ret = (void*)fbl_parametered_tap->pParameterBlock;

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
