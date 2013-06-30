#include                "../libFireBird.h"

void Appl_ShoutCast(void)
{
  #ifdef DEBUG_FIREBIRDLIB
    CallTraceEnter("Appl_ShoutCast");
  #endif

  void                  (*__Appl_ShoutCast)(void *OsdOp);

  __Appl_ShoutCast = (void*)FIS_fwAppl_ShoutCast();
  if(__Appl_ShoutCast) __Appl_ShoutCast(NULL);

  #ifdef DEBUG_FIREBIRDLIB
    CallTraceExit(NULL);
  #endif
}
