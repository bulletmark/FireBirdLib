#include                <stdio.h>
#include                "../libFireBird.h"

void* TAP_MemAlloc_Chk(char *Comment, dword size)
{
  TRACEENTER();

  void                 *ret;

  ret = TAP_MemAlloc(size);

  if(!ret && Comment) LogEntryFBLibPrintf(TRUE, "TAP_MemAlloc_Chk Warning: TAP_MemAlloc(%d) returned NULL pointer @ %s", size, Comment);

  TRACEEXIT();
  return ret;
}
