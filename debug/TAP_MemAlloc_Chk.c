#include                <stdio.h>
#include                "../libFireBird.h"

void* TAP_MemAlloc_Chk(char *Comment, dword size)
{
  void                 *ret;

#ifdef DEBUG_FIREBIRDLIB
  CallTraceEnter("TAP_MemAlloc_Chk");
#endif

  ret = TAP_MemAlloc(size);

  if(!ret) TAP_Print("TAP_MemAlloc_Chk Warning: TAP_MemAlloc(%d) returned NULL pointer @ %s\n", size, Comment);

#ifdef DEBUG_FIREBIRDLIB
  CallTraceExit(NULL);
#endif

  return ret;
}
