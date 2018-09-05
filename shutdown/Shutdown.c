#include "FBLib_shutdown.h"
#include "libFireBird.h"

bool Shutdown(TaskEnum Task)
{
  TRACEENTER;

  bool ret;

  ret = PutDevEvent(Task, 0);

  TRACEEXIT;
  return ret;
}
