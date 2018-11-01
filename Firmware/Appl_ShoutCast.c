#include                "libFireBird.h"

void Appl_ShoutCast(void)
{
  TRACEENTER();

  void                  (*__Appl_ShoutCast)(void *OsdOp);

  __Appl_ShoutCast = (void*)FIS_fwAppl_ShoutCast();
  if(__Appl_ShoutCast) __Appl_ShoutCast(NULL);

  TRACEEXIT();
}
