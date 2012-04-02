#include "FBLib_shutdown.h"
#include "../libFireBird.h"

bool Shutdown(TaskEnum Task)
{
  return PutDevEvent(Task, 0);
}
