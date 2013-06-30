#include "FBLib_shutdown.h"
#include "../libFireBird.h"

bool Shutdown(TaskEnum Task)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Shutdown");
  #endif

  bool ret;

  ret = PutDevEvent(Task, 0);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif

  return ret;
}
