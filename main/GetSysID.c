#include "libFireBird.h"

word GetSysID(void)
{
  TRACEENTER();

  word ret = TAP_GetSystemId();

  TRACEEXIT();
  return ret;
}
