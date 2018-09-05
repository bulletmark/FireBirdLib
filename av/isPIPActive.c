#include "libFireBird.h"

bool isPIPActive(void)
{
  TRACEENTER;

  byte *_isPipActive = (byte*)FIS_vIsPipActive();

  TRACEEXIT;
  return _isPipActive ? *_isPipActive : FALSE;
}
